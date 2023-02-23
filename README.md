# English

**I recommend using this feature only on btrfs partitions, as the working mode prevents data corruption.**

You may recall that for many years there has always been a discussion about using a nobarrier to mount the file system, but the risk of corrupting the system when power is lost does not outweigh the performance gain.

So why not use a similar feature, disabling fsync and fdatasync, but at the application level and not the file system?

In my initial tests I did several forced restarts without any problem of corrupting the system, however the data recording actually occurs on the disk when the partition commit time is reached, in general every 30 seconds, I reduced it to 10 seconds, you can customize this in the /etc/fstab file.

I have had several performance gains using this method, mainly in browsers, but the time to open the file manager and practically all other programs has also been reduced.

To test on your system just use these 3 commands as root in the terminal:

sudo su

wget https://raw.githubusercontent.com/biglinux/disable-fsync/main/disable-fsync/usr/lib/disable-fsync.so -O /usr/lib/disable-fsync.so

echo "/usr/lib/disable-fsync.so" >> /etc/ld.so.preload

ldconfig

----------------

**More detailed explanation, but still easy to understand, first about what fsync is:**

When a program saves a file, that file first goes to cache in RAM memory, which is much faster than storage, then after that the file will actually be saved to the storage device, usually a hard drive or an SSD.

For the program to know if the file has actually been saved to storage, it is using fsync.

Usually when performing an fsync the program interrupts the processes and waits for a response from the system confirming that the file was saved, after that the program follows its processes.

A DDR2-400 RAM memory, technology from 2003, has a speed of 3200 MB/s, a DDR4-4400 RAM memory reaches 35200 MB/s, or even a popular and already old DDR3-1333 reaches 10667 MB/s.

In 2021 few NVME storage devices, the fastest currently, reach 3200 MB/s, most SSDs reach 400 MB/s and rotational hard drives around 150 MB/s.

In almost all computers the speed difference between the RAM memory and the storage device is at least 10x, often the difference is greater than 100x.

At the same time, fsync is the way to ensure that that information has actually been saved and in the event of a system crash or power failure, that information is stored.

It's a question of balance between ensuring data integrity or ensuring performance.

For a long time there was a discussion about using the nobarrier option in the /etc/fstab file, but this always brought a lot of file corruption in situations of power failure, nobarrier is a way to bypass fsync directly on the file system.

Here the focus is only on the BTRFS filesystem, which has higher levels of checks than most filesystems, which prevents data corruption.

The way I managed to achieve a good level of performance with minimal loss of data integrity was to use LD_PRELOAD to disable fsync and fdatasync at the application level and not the file system level.

For more performance I also use these settings in BTRFS, in the /etc/fstab file:
noatime,space_cache=v2,discard=async,autodefrag,compress-force=zstd:2,commit=10

The commit=10 option helps improve data integrity by reducing the time the file system waits to save files that are cached in RAM from 30 seconds to 10 seconds, making it very unlikely that more than the files will be lost. last 10 seconds of files saved in case of power failure.

This configuration brought great performance gains, especially on computers that still use rotational HD.


# Português

**Recomendo utilizar esse recurso apenas em partições btrfs, pois o modo de funcionamento evita corrompimento de dados.**

Talvez você se recorde que a muitos anos se discutia sempre sobre o uso de nobarrier para montar o sistema de arquivos, mas o risco de corromper o sistema ao faltar energia não compensava o ganho de desempenho.

Então por que não utilizar um recurso similar, desativando o fsync e o fdatasync, mas no nível de aplicativo e não do sistema de arquivos?

Nos meus testes iniciais fiz vários reinícios forçados sem nenhum problema de corromper o sistema, porém a gravação dos dados ocorrem realmente no disco quando o tempo de commit da partição é atingido, em geral a cada 30 segundos, eu reduzi para 10 segundos, você pode personalizar isso no arquivo /etc/fstab.

Tive vários ganhos de desempenho utilizando esse método, principalmente nos navegadores, mas o tempo para abrir o gerênciador de arquivos e praticamente todos os outros programas também foi reduzido.

Para testar no seu sistema basta utilizar esses 3 comandos como root no terminal:

sudo su

wget https://raw.githubusercontent.com/biglinux/disable-fsync/main/disable-fsync/usr/lib/disable-fsync.so -O /usr/lib/disable-fsync.so

echo "/usr/lib/disable-fsync.so" >> /etc/ld.so.preload

ldconfig


------------

**Explicação mais detalhada, mas ainda de fáci compreensão, primeiro sobre o que é o fsync:**

Quando um programa salva um arquivo, esse arquivo primeiro vai para a cache em memória RAM, que é muito mais rápida que o armazenamento, então depois disso o arquivo será realmente salvo no dispositivo de armazenamento, geralmente um HD ou um SSD.

Para o programa saber se o arquivo já foi realmente salvo no armazenamento, é utilizando o fsync. 

Geralmente ao efetuar um fsync o programa interrompe os processos e aguarda uma resposta do sistema confirmando que o arquivo foi salvo, após isso o programa segue seus processos.

Uma memória RAM DDR2-400, tecnologia de 2003, tem velocidade de 3200 MB/s, uma memória RAM DDR4-4400 chega a 35200 MB/s, ou mesmo uma popular e já antiga DDR3-1333 chega a 10667 MB/s.

Em 2021 poucos dispositivos de armazenamento NVME, os mais rápidos atualmente, chegam a 3200 MB/s, a maioria dos SSDs chegam a 400 MB/s e os HDs rotacionais em torno de 150 MB/s.

Em quase todos os computadores a diferença de velocidade entre a memória RAM e o dispositivo de armazenamento é no mínimo 10x, muitas vezes a diferença é maior que 100x.

Ao mesmo tempo o fsync é a forma de assegurar que aquela informação realmente foi salva e caso ocorra travamento no sistema ou falta de energia, aquela informação está armazenada.

É uma questão de equilíbrio entre assegurar a integridade dos dados ou assegurar o desempenho.

Por muito tempo ocorreu a discussão sobre utilizar a opção nobarrier no arquivo /etc/fstab, porém isso sempre trouxe grande quantidade de corrompimento de arquivos em situação de falta de energia, o nobarrier é uma forma de ignorar o fsync diretamente no sistema de arquivos.

Aqui o foco é apenas no sistema de arquivos BTRFS, que possui níveis de checagens maiores que a maioria dos sistemas de arquivos, o que evita corrompimento dos dados.

A forma que consegui atingir um bom nível de desempenho com o mínimo de perda na integridade dos dados foi utilizar o LD_PRELOAD para desativar o fsync e o fdatasync no nível do aplicativo e não do sistema de arquivos.

Para ter mais desempenho também utilizo essas configurações no BTRFS, no arquivo /etc/fstab:
noatime,space_cache=v2,discard=async,autodefrag,compress-force=zstd:2,commit=10

A opção commit=10 ajuda a melhorar a integridade dos dados, reduzindo de 30 segundos para 10 segundos o tempo que o sistema de arquivos aguarda até salvar os arquivos que estão em cache na memória RAM, tornando bastante improvável que sejam perdidos mais do que os últimos 10 segundos de arquivos salvos no caso de falta de energia.

Essa configuração trouxe grandes ganhos de desempenho, principalmente em computadores que ainda utilizam HD rotacional.
