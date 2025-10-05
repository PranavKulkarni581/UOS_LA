Files included (31-45) with short compile/run instructions:

31_vfork_launch.c
  gcc 31_vfork_launch.c -o vfork_launch
  ./vfork_launch /bin/ls -l

32_wait_fork.c
  gcc 32_wait_fork.c -o wait_fork
  ./wait_fork

33_exec_variants.c
  gcc 33_exec_variants.c -o exec_variants
  ./exec_variants

34_exit_wait.c
  gcc 34_exit_wait.c -o exit_wait
  ./exit_wait

35_kill_unrelated_receiver.c
35_kill_unrelated_sender.c
  gcc 35_kill_unrelated_receiver.c -o kill_recv
  gcc 35_kill_unrelated_sender.c -o kill_send
  Run receiver then: ./kill_send <pid>

36_kill_related.c
  gcc 36_kill_related.c -o kill_related
  ./kill_related

37_alarm_input_timeout.c
  gcc 37_alarm_input_timeout.c -o alarm_input
  ./alarm_input

38_alarm_clock.c
  gcc 38_alarm_clock.c -o alarm_clock
  ./alarm_clock 5

39_stat.c
  gcc 39_stat.c -o stat_info
  ./stat_info filename

40_fstat.c
  gcc 40_fstat.c -o fstat_info
  ./fstat_info filename

41_multithreaded_chat_c.c
  gcc 41_multithreaded_chat_c.c -o mt_chat -pthread
  ./mt_chat

42_three_threads_numbers.c
  gcc 42_three_threads_numbers.c -o three_threads -pthread
  ./three_threads

43_pthread_example.c
  gcc 43_pthread_example.c -o pthread_example -pthread
  ./pthread_example

44_producer_consumer_java.java
  javac 44_producer_consumer_java.java
  java producer_consumer

45_calc.sh
  chmod +x 45_calc.sh
  ./45_calc.sh

Note: Test on Linux. Some programs use signals/system V shared resources.
