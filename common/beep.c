/*

	Beep no som da placa mae
	
	Testar:

		#! /bin/sh

		beep -f 500 -l 700
		beep -f 480 -l 400
		beep -f 470 -l 250
		beep -f 530 -l 300 -D 100
		beep -f 500 -l 300 -D 100
		beep -f 500 -l 300
		beep -f 400 -l 600
		beep -f 300 -l 500
		beep -f 350 -l 700
		beep -f 250  -l 600

*/


#include <fcntl.h>
#include <getopt.h>
#include <signal.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <linux/kd.h>

#ifndef BEEP_CLOCK_TICK_RATE
#define BEEP_CLOCK_TICK_RATE 1193180
#endif

/* Meaningful Defaults */
#define BEEP_DEFAULT_FREQ       440.0 /* Middle A */
#define BEEP_DEFAULT_LENGTH     200   /* milliseconds */
#define BEEP_DEFAULT_REPS       1
#define BEEP_DEFAULT_DELAY      100   /* milliseconds */
#define BEEP_DEFAULT_END_DELAY  BEEP_NO_END_DELAY
#define BEEP_DEFAULT_STDIN_BEEP BEEP_NO_STDIN_BEEP

/* Other Constants */
#define BEEP_NO_END_DELAY    0
#define BEEP_YES_END_DELAY   1

#define BEEP_NO_STDIN_BEEP   0
#define BEEP_LINE_STDIN_BEEP 1
#define BEEP_CHAR_STDIN_BEEP 2

typedef struct beep_parms_t {
	float freq;     /* tone frequency (Hz)      */
	int length;     /* tone length    (ms)      */
	int reps;       /* # of repetitions         */
	int delay;      /* delay between reps  (ms) */
	int end_delay;  /* do we delay after last rep? */
	int stdin_beep;
	/* are we using stdin triggers?  We have three options:
		- just beep and terminate (default)
		- beep after a line of input
		- beep after a character of input
		In the latter two cases, pass the text back out again,
		so that beep can be tucked appropriately into a text-
		processing pipe.
	*/
	struct beep_parms_t *next;  /* in case -n/--new is used. */
} beep_parms_t;

/* Momma taught me never to use globals, but we need something the signal 
   handlers can get at.*/
int console_fd = -1;

/* If we get interrupted, it would be nice to not leave the speaker beeping in
   perpetuity. */
void handle_signal(int signum) {
	switch(signum) {
	case SIGINT:
		if(console_fd >= 0) {
			// Kill the sound, quit gracefully
			ioctl(console_fd, KIOCSOUND, 0);
			close(console_fd);
			exit(signum);
		} else {
			// Just quit gracefully
			exit(signum);
		}
	}
}


/* print usage and exit */
void help_beep(){
	printf("beep\nUsage:\nbeep [-f freq] [-l length] [-r reps] [-d delay] [-D delay] [-s] [-c]\n");
	printf("    beep [Options...] [-n] [--new] [Options...] ... \n");
	printf("    beep [-h] [--help]\n");
	exit(1);
}


/* Parse the command line.  argv should be untampered, as passed to main.
 * Beep parameters returned in result, subsequent parameters in argv will over-
 * ride previous ones.
 * 
 * Currently valid parameters:
 *  "-f <frequency in Hz>"
 *  "-l <tone length in ms>"
 *  "-r <repetitions>"
 *  "-d <delay in ms>"
 *  "-D <delay in ms>" (similar to -d, but delay after last repetition as well)
 *  "-s" (beep after each line of input from stdin, echo line to stdout)
 *  "-c" (beep after each char of input from stdin, echo char to stdout)
 *  "-h/--help"
 *  "-v/-V/--version"
 *  "-n/--new"
 *
 * March 29, 2002 - Daniel Eisenbud points out that c should be int, not char,
 * for correctness on platforms with unsigned chars.
 */
void parse_command_line(const int argc, const char **argv, beep_parms_t *result) {
	int c;

	struct option opt_list[4] = {
		{"help", 0, NULL, 'h'},
		{"version", 0, NULL, 'V'},
		{"new", 0, NULL, 'n'},
		{0,0,0,0}
	};

	while((c = getopt_long(argc, argv, "f:l:r:d:D:schn", opt_list, NULL)) != EOF) {
		int argval = -1;    /* handle parsed numbers for various arguments */
		float argfreq = -1; 
		switch(c) {
			case 'f':  /* freq */
				if(!sscanf(optarg, "%f", &argfreq) || (argfreq >= 20000 /* ack! */) ||  (argfreq <= 0))
					help_beep(argv[0]);
				else
					result->freq = argfreq;
				//-
				break;

			case 'l' : /* length */
				if(!sscanf(optarg, "%d", &argval) || (argval < 0))
					help_beep(argv[0]);
				else
					result->length = argval;
				//-
				break;

			case 'r' : /* repetitions */
				if(!sscanf(optarg, "%d", &argval) || (argval < 0))
					help_beep(argv[0]);
				else
					result->reps = argval;
				//-
				break;

			case 'd' : /* delay between reps - WITHOUT delay after last beep*/
				if(!sscanf(optarg, "%d", &argval) || (argval < 0))
					help_beep(argv[0]);
				else {
					result->delay = argval;
					result->end_delay = BEEP_NO_END_DELAY;
				}
				break;

			case 'D' : /* delay between reps - WITH delay after last beep */
				if(!sscanf(optarg, "%d", &argval) || (argval < 0))
					help_beep(argv[0]);
				else {
					result->delay = argval;
					result->end_delay = BEEP_YES_END_DELAY;
				}
				break;

			case 's' :
				result->stdin_beep = BEEP_LINE_STDIN_BEEP;
				break;

			case 'c' :
				result->stdin_beep = BEEP_CHAR_STDIN_BEEP;
				break;

			case 'n' : /* also --new - create another beep */
				result->next = (beep_parms_t *)malloc(sizeof(beep_parms_t));
				result->next->freq       = BEEP_DEFAULT_FREQ;
				result->next->length     = BEEP_DEFAULT_LENGTH;
				result->next->reps       = BEEP_DEFAULT_REPS;
				result->next->delay      = BEEP_DEFAULT_DELAY;
				result->next->end_delay  = BEEP_DEFAULT_END_DELAY;
				result->next->stdin_beep = BEEP_DEFAULT_STDIN_BEEP;
				result->next->next       = NULL;
				result = result->next; /* yes, I meant to do that. */
				break;

			case 'h' : /* notice that this is also --help */
			default :
				help_beep(argv[0]);

		} // switch
	} // while
}  

void play_beep(beep_parms_t parms) {

	// loop counter
	int i; 

	// try to snag the console 
	if((console_fd = open("/dev/console", O_WRONLY)) == -1) {
		fprintf(stderr, "Could not open /dev/console for writing.\n");
		
		// Output the only beep we can, in an effort to fall back on usefulness
		printf("\a"); 
		perror("open");
		exit(1);
	}

	// Beep
	for (i = 0; i < parms.reps; i++) {
		// start beep
		if(ioctl(console_fd, KIOCSOUND, (int)(BEEP_CLOCK_TICK_RATE/parms.freq)) < 0) {
			// Output the only beep we can, in an effort to fall back on usefulness
			printf("\a");
			perror("ioctl");
		}

		// Look ma, I'm not ansi C compatible!
		// wait
		usleep(1000*parms.length);
		// stop beep
		ioctl(console_fd, KIOCSOUND, 0);

		// wait
		if(parms.end_delay || (i+1 < parms.reps))
			usleep(1000*parms.delay);
		//-
	}

	close(console_fd);
}



int main_beep(const char *progname, const int argc, const char **argv) {
	char sin[4096], *ptr;

	beep_parms_t *parms = (beep_parms_t *)malloc(sizeof(beep_parms_t));
	parms->freq       = BEEP_DEFAULT_FREQ;
	parms->length     = BEEP_DEFAULT_LENGTH;
	parms->reps       = BEEP_DEFAULT_REPS;
	parms->delay      = BEEP_DEFAULT_DELAY;
	parms->end_delay  = BEEP_DEFAULT_END_DELAY;
	parms->stdin_beep = BEEP_DEFAULT_STDIN_BEEP;
	parms->next       = NULL;

	signal(SIGINT, handle_signal);
	parse_command_line(argc, argv, parms);

	/* this outermost while loop handles the possibility that -n/--new has been
	used, i.e. that we have multiple beeps specified. Each iteration will
	play, then free() one parms instance. */
	while(parms) {
		beep_parms_t *next = parms->next;

		if(parms->stdin_beep) {
			// in this case, beep is probably part of a pipe, in which case POSIX 
			// says stdin and out should be fuly buffered.  This however means very 
			// laggy performance with beep just twiddling it's thumbs until a buffer
			// fills. Thus, kill the buffering.  In some situations, this too won't 
			// be enough, namely if we're in the middle of a long pipe, and the 
			// processes feeding us stdin are buffered, we'll have to wait for them,
			// not much to  be done about that.
			setvbuf(stdin, NULL, _IONBF, 0);
			setvbuf(stdout, NULL, _IONBF, 0);

			while(fgets(sin, 4096, stdin)) {
				if(parms->stdin_beep == BEEP_CHAR_STDIN_BEEP) {
					for(ptr=sin;*ptr;ptr++) {
						putchar(*ptr);
						fflush(stdout);
						play_beep(*parms);
					}
				} else {
					fputs(sin, stdout);
					play_beep(*parms);
				}
			}
		} else {
			play_beep(*parms);
		}

		// Junk each parms struct after playing it
		free(parms);
		parms = next;
	}

	return EXIT_SUCCESS;

}










