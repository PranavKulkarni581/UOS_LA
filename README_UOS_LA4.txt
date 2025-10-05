UOS_LA4.zip - Programs 71 to 87

71: Utilities (cat, ls, cp, mv, head)
  gcc 71_cat.c -o cat_sim
  gcc 71_ls_sim.c -o ls_sim
  gcc 71_cp_sim.c -o cp_sim
  gcc 71_mv_sim.c -o mv_sim
  gcc 71_head.c -o head_sim

72: Semaphore order f1 before f2
  gcc 72_sem_order.c -o sem_order -pthread
  ./sem_order

73-76: Message queue dialog
  gcc 73_msg_hi_hello_send.c -o msg_send
  gcc 73_msg_hi_hello_recv.c -o msg_recv
  gcc 73_msg_hi_hello_reply_recv.c -o msg_reply
  Run in sequence: ./msg_send ; ./msg_recv ; ./msg_reply

77: TCP demo (server/client)
  gcc 77_tcp_demo_server.c -o tcp_demo_server
  gcc 77_tcp_demo_client.c -o tcp_demo_client

78: UDP demo (server/client)
  gcc 78_udp_demo_server.c -o udp_demo_server
  gcc 78_udp_demo_client.c -o udp_demo_client

79: Echo TCP (iterative/concurrent)
  gcc 79_echo_tcp_iter.c -o echo_iter
  gcc 79_echo_tcp_conc.c -o echo_conc

80: Echo UDP
  gcc 80_echo_udp.c -o echo_udp

81-83: Pipes
  gcc 81_pipe_parent_child.c -o pipe_p2c
  gcc 82_pipe_send_file.c -o pipe_send_file
  gcc 83_pipe_filter_uc2lc.c -o pipe_filter

84: Semaphore with fork demo (uses POSIX named semaphore)
  gcc 84_sem_fork_demo.c -o sem_fork -pthread
  ./sem_fork

85: Semaphore init/P/V programs (System V)
  gcc 85_sem_init.c -o sem_init
  gcc 85_sem_P.c -o sem_P
  gcc 85_sem_V.c -o sem_V
  Run sem_init once, then sem_P and sem_V as separate programs.

86: lockf demo
  gcc 86_lockf_demo.c -o lockf_demo
  ./lockf_demo

87: flock demo (using fcntl)
  gcc 87_flock_demo.c -o flock_demo
  ./flock_demo

Note: Test on Linux. Some programs require appropriate permissions or for multiple terminals to run concurrently.
