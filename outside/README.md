# Binarios independentes

## 1 - netmirror

Servidor/Cliente ECHO com suporte a amplificacao. Criado para testar capacidade de ping-pong de dados
via TCP e criação de laboratórios para melhorar a performance de servidores, roteadores e backbones.

Porta padrao: 7000

Compilando:
gcc netmirror.c -o /usr/bin/netmirror

## Lado servidor:

- servidor echo simples
```
netmirror   
```

- amplificar echo de respostas em 10x
```
netmirror -a 10
```

- amplificar echo de respostas em 100x, modo IPv6
```
netmirror -a 10 -6
```

- amplificar echo de respostas em 20x, modo IPv6, envios de 10kbytes por eco, texto com letra A
```
netmirror -a 10 -6 -r 10240 -c 65
```

## Lado cliente:
- Envia buffer de eco e finaliza:
```
netmirror -c 192.168.0.1
```

- Envia buffer de eco infinitamente:
```
netmirror -c 192.168.0.1 -f
```

- Envia buffer de eco infinitamente com buffer de 2kbytes
```
netmirror -c 192.168.0.1 -f -r 2048
```



