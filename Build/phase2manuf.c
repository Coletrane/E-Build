/**
// Pick a random order size [1000-2000]
    order_init();
    printf("Initial order size: %d\n", order_size);

    pthread_mutex_init(&mutex, NULL);

    thread_params_t thrd_param[6];      //Will not use thrd_param[0]
    pthread_t thread[6];

    // Init thread params and create the threads
    int i;
    for (i = 1; i < THREADS + 1; i++)
    {
        thrd_param[i].iterations = 0;
        thrd_param[i].num_items = 0;
        thrd_param[i].capacity = (random() % 41) + 10;
	    thrd_param[i].duration = (random() % 5) + 1;
        thrd_param[i].tid = i;
        pthread_create(&thread[i], NULL, manufacturing_line, &thrd_param[i]);
    }

    // Wait for the threads to finish
    for (i = 1; i < THREADS + 1; i++)
    {
        pthread_join(thread[i], NULL);
    }

    //Confirm end of manufacturing
    printf("All parts manufactured.\n");

    //Destroy mutex
    pthread_mutex_destroy(&mutex);

    // Thread function
void *manufacturing_line(void *ptr)
{
    thread_params_t *param = ptr;

    printf("Factory line %d has been dispatched with capacity: %d and duration: %d\n"
            , param->tid, param->capacity, param->duration);

    while (order_size > 0)
    {
        // Iterations 1 to n-1
        if (order_size > param->capacity)
        {
            // Lock mutex to update order_size
            pthread_mutex_lock(&mutex);
            order_size -= param->capacity;
            printf("Order size: %d\n", order_size);
            pthread_mutex_unlock(&mutex);

            // Update lines' parameters
            param->iterations++;
            param->num_items += param->capacity;
            sleep(param->duration);
            printf("Factory line %d iteration complete. All time iterations: %d All time parts made: %d\n"
                   ,param->tid, param->iterations, param->num_items);
        }
        // Last iteration
        else
        {
            // Lock mutex to update order_size
            param->num_items += order_size;
            pthread_mutex_lock(&mutex);
            order_size = 0;
            printf("Order size: %d\n", order_size);
            pthread_mutex_unlock(&mutex);

            // Update lines' parameters
            param->iterations++;
            sleep(param->duration);
            printf("Factory line %d iteration complete. All time iterations: %d All time parts made: %d\n"
                   ,param->tid, param->iterations, param->num_items);
        }
    }
} */
