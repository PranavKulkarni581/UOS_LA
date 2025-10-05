UOS_LA3.zip - Programs 44 to 70

Files and short instructions:

44_producer_consumer_java_multithread.java
  javac 44_producer_consumer_java_multithread.java
  java producer_consumer_mt

45_calc.sh
  chmod +x 45_calc.sh
  ./45_calc.sh

46_digital_clock.sh
  chmod +x 46_digital_clock.sh
  ./46_digital_clock.sh

47_ping_check.sh
  chmod +x 47_ping_check.sh
  ./47_ping_check.sh [host]

48_sort_numbers.sh
  chmod +x 48_sort_numbers.sh
  ./48_sort_numbers.sh

49_color_hello.sh
  chmod +x 49_color_hello.sh
  ./49_color_hello.sh

50_file_exists.sh
  chmod +x 50_file_exists.sh
  ./50_file_exists.sh <folder> <filename>

51_disk_info.sh
  chmod +x 51_disk_info.sh
  ./51_disk_info.sh

52_locate_file.sh
  chmod +x 52_locate_file.sh
  ./52_locate_file.sh <name>

53_download_wget.sh
54_download_wget_dup.sh
  chmod +x 53_download_wget.sh 54_download_wget_dup.sh
  ./53_download_wget.sh <url>

55_list_users.sh
  chmod +x 55_list_users.sh
  ./55_list_users.sh

56_primes_recursive.py
  python3 56_primes_recursive.py <limit>

57_pyramid.c
  gcc 57_pyramid.c -o pyramid
  ./pyramid

58_word_freq.py
  python3 58_word_freq.py <file>

59_history_top5.sh
  chmod +x 59_history_top5.sh
  ./59_history_top5.sh

60_exec_check.sh
  chmod +x 60_exec_check.sh
  ./60_exec_check.sh <filename>

61_wonderland_freq.sh
  chmod +x 61_wonderland_freq.sh
  ./61_wonderland_freq.sh wonderland.txt

62_concat_files.sh
  chmod +x 62_concat_files.sh
  ./62_concat_files.sh file1 file2 ...

63_lftp_download.sh
  chmod +x 63_lftp_download.sh
  ./63_lftp_download.sh <host> <user> <remote-file>

64_prod_cons_sem_threads.c
  gcc 64_prod_cons_sem_threads.c -o prodcons_mt -pthread
  ./prodcons_mt

65_reader_writer_sem.c
  gcc 65_reader_writer_sem.c -o rw_sem -pthread
  ./rw_sem

66_msg_queue_chat_three.c
  gcc 66_msg_queue_chat_three.c -o msgchat
  ./msgchat 1   (in three terminals use 1,2,3)

67_shm_send_recv.c
  gcc 67_shm_send_recv.c -o shm_sr
  ./shm_sr        (writer)
  ./shm_sr read   (reader)

68_shm_file_transfer_simple.c
  gcc 68_shm_file_transfer_simple.c -o shm_ft
  ./shm_ft write infile
  ./shm_ft read outfile

69_shm_sort3.c
  gcc 69_shm_sort3.c -o shm_sort3
  ./shm_sort3

70_shm_ops_demo.c
  gcc 70_shm_ops_demo.c -o shm_ops
  ./shm_ops

Note: Test on Linux. Some programs require sudo or appropriate permissions.
