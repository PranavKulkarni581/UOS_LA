Files included and short compile/run instructions:

21_dining_philosophers.c
  gcc 21_dining_philosophers.c -o dining -pthread
  ./dining

22_prod_consumer_bounded.c
  gcc 22_prod_consumer_bounded.c -o prodcons
  ./prodcons

23_rw_writer_priority.c
  gcc 23_rw_writer_priority.c -o rw_priority
  ./rw_priority

24_tcp_echo_concurrent_fork.c
  gcc 24_tcp_echo_concurrent_fork.c -o tcp_echo
  ./tcp_echo
  Use a tcp client (nc 127.0.0.1 9090) to test.

25_udp_file_transfer_server.c
25_udp_file_transfer_client.c
  gcc 25_udp_file_transfer_server.c -o udp_server
  gcc 25_udp_file_transfer_client.c -o udp_client
  Run server then client.

26_dist_comp_server.c
  gcc 26_dist_comp_server.c -o dist_server
  Run server; connect via: printf "FACT 5\n" | nc 127.0.0.1 9092

27_chat_server.c
  gcc 27_chat_server.c -o chat -pthread
  Run server; connect via: nc 127.0.0.1 9093 from multiple terminals.

28_five_children.c
  gcc 28_five_children.c -o five_children
  ./five_children

29_vfork_login.c
  gcc 29_vfork_login.c -o vfork_login
  ./vfork_login

30_launch_app.c
  gcc 30_launch_app.c -o launch_app
  ./launch_app /bin/ls -l

Notes:
- Some programs use System V semaphores/shm and require root or appropriate permissions on some systems.
- Test on Linux.
