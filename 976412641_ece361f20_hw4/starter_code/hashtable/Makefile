C = gcc
CFLAGS = -Wall -g -std=c99
HDRS = MLSapp_Helpers.h hash_table.h
OBJS = hw4_MLSapp_Helpers.c hash_table.c test_hashtable.c

hash_table_test : 
	$(C)$(FLAGS) -o hash_table_test hw4_MLSapp_Helpers.c hash_table.c test_hashtable.c -lm

clean:
	rm hash_table_test
