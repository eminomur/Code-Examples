#include <stdio.h>
#include <pthread.h>
#include <stdbool.h>
#include <errno.h>

struct philosopher {
	const char *name;
	pthread_mutex_t *left_fork_mutex;
	pthread_mutex_t *right_fork_mutex;
};

void
eat(struct philosopher *p)
{
	while (true) {
		pthread_mutex_lock(p->left_fork_mutex);
		int lock_status = pthread_mutex_trylock(p->right_fork_mutex);
		if (!lock_status) {
			printf("%s is eating.\n", p->name);
			break;
		} else if (lock_status == EBUSY) {
			pthread_mutex_unlock(p->left_fork_mutex);
			pthread_yield();
		} else {
			// It seems something bad happened, run!
		}
	}
	pthread_mutex_unlock(p->left_fork_mutex);
	pthread_mutex_unlock(p->right_fork_mutex);
}

void
think(struct philosopher *p)
{
	printf("%s is thinking.\n", p->name);
}

void *
live(void *arg)
{
	for (int i = 0; i < 7; ++i) {
		if (i % 2 == 0) {
			think((struct philosopher *) arg);
		} else {
			eat((struct philosopher *) arg);
		}
	}
	pthread_exit(NULL);
}

int
main(void)
{
	// t means thread
	pthread_t t1, t2, t3, t4, t5;
	// f means fork
	pthread_mutex_t f1, f2, f3, f4, f5;

	pthread_mutex_init(&f1, NULL);
	pthread_mutex_init(&f2, NULL);
	pthread_mutex_init(&f3, NULL);
	pthread_mutex_init(&f4, NULL);
	pthread_mutex_init(&f5, NULL);

	// p means philosopher
	struct philosopher p1 = {
		.name = "Philosopher X",
		.left_fork_mutex = &f1,
		.right_fork_mutex = &f5
	};

	struct philosopher p2 = {
		.name = "Philosopher Y",
		.left_fork_mutex = &f2,
		.right_fork_mutex = &f1
	};

	struct philosopher p3 = {
		.name = "Philosopher Z",
		.left_fork_mutex = &f3,
		.right_fork_mutex = &f2
	};

	struct philosopher p4 = {
		.name = "Philosopher T",
		.left_fork_mutex = &f4,
		.right_fork_mutex = &f3
	};

	struct philosopher p5 = {
		.name = "Philosopher Q",
		.left_fork_mutex = &f5,
		.right_fork_mutex = &f4
	};

	pthread_create(&t1, NULL, live, &p1);
	pthread_create(&t2, NULL, live, &p2);
	pthread_create(&t3, NULL, live, &p3);
	pthread_create(&t4, NULL, live, &p4);
	pthread_create(&t5, NULL, live, &p5);

	pthread_join(t1, NULL);
	pthread_join(t2, NULL);
	pthread_join(t3, NULL);
	pthread_join(t4, NULL);
	pthread_join(t5, NULL);

	pthread_mutex_destroy(&f1);
	pthread_mutex_destroy(&f2);
	pthread_mutex_destroy(&f3);
	pthread_mutex_destroy(&f4);
	pthread_mutex_destroy(&f5);

	return (0);
}
