# English

You may recall that for many years there has always been a discussion about using a nobarrier to mount the file system, but the risk of corrupting the system when power is lost does not outweigh the performance gain.

So why not use a similar feature, disabling fsync and fdatasync, but at the application level and not the file system?

In my initial tests I did several forced restarts without any problem of corrupting the system, however the data recording actually occurs on the disk when the partition commit time is reached, in general every 30 seconds, I reduced it to 10 seconds, you can customize this in the /etc/fstab file.

I have had several performance gains using this method, mainly in browsers, but the time to open the file manager and practically all other programs has also been reduced.

To test on your system just use these 3 commands as root in the terminal:

wget https://raw.githubusercontent.com/biglinux/disable-fsync/main/disable-fsync/usr/lib/disable-fsync.so -O /usr/lib/disable-fsync.so

echo "/usr/lib/disable-fsync.so" >> /etc/ld.so.preload

sudo ldconfig


# Português

Talvez você se recorde que a muitos anos se discutia sempre sobre o uso de nobarrier para montar o sistema de arquivos, mas o risco de corromper o sistema ao faltar energia não compensava o ganho de desempenho.

Então por que não utilizar um recurso similar, desativando o fsync e o fdatasync, mas no nível de aplicativo e não do sistema de arquivos?

Nos meus testes iniciais fiz vários reinícios forçados sem nenhum problema de corromper o sistema, porém a gravação dos dados ocorrem realmente no disco quando o tempo de commit da partição é atingido, em geral a cada 30 segundos, eu reduzi para 10 segundos, você pode personalizar isso no arquivo /etc/fstab.

Tive vários ganhos de desempenho utilizando esse método, principalmente nos navegadores, mas o tempo para abrir o gerênciador de arquivos e praticamente todos os outros programas também foi reduzido.

Para testar no seu sistema basta utilizar esses 3 comandos como root no terminal:


wget https://raw.githubusercontent.com/biglinux/disable-fsync/main/disable-fsync/usr/lib/disable-fsync.so -O /usr/lib/disable-fsync.so

echo "/usr/lib/disable-fsync.so" >> /etc/ld.so.preload

sudo ldconfig
