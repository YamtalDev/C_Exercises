/******************************************************************************
                                        ▄▄▀▀▀▀████▓▓░░  ░
                                     ▄█▓░░   ░▓█▓
                                   ▄█▓░░    ░▓█░
                                  █▓░░░░   ░▓█░
                                ▄█▓░░░    ░░▓█░
        ▄▄▄              ▄▄▄▄█▄█▓▓▀▀▀▓███▄▄▓██▓░ ░
       █░  █         ▄▄▓▓▓▓░░░░░░░░░░░░░░░▓████▄▄                      ▄▄▄▄▄▄▓
      █    ▓█    ▄▄▓▓▓▓░▓░░░   ░░░░░░░░░░░░░░░▓▓▓█▄▄     ▄        ▄▄▓▓▓░░░░█▀
       █  ▓█   ▄█▓░▄██▓░░       ░  ░░░░░░ ░░░░░░▓▓▓▓██▄    ▄   ░▄▓▓▓░░  ░▓█▓
        ▀▀▀  ▄█▓░ ▄▄▄▄▄ ░░           ░░░   ░  ▄▄▄ ░░▓▓▓█▄ ▀▓▀ ░█▓▓░░   ░▓█▓
      ▄▄    ██▓░▄▀  ░░▓█▓░░       ░  ░░      █░  █  ░░░▓▓█▄  ▓█▓▓░░   ░▓▓█░
     █ ▓█  ██▓░▓█     ░▓█▓░░   ░   ░░░      █░  ░▓█   ░░▓▓██▓█▓▓░    ░░▓▓█
      ▀▀  ██▓▓░█▓      ░▓░░   ░ ░            █ ░▓█     ░░░▓███▓░ ░  ░░░▓█▓
   ▄▄  ▄ ██▓▓░ █░  ▄▄▄  ░░     ░    ▄▄▄▄▄     ▀▀▀ ▄  ░  ░░░▓█▓░    ░░░▓▓█
  █ ▓█  ███▓▓░▄█▄▄██▄█▄▄▄░░     ▄▓▓▓░░░ ░▀  ░░░          ░░▓█▓    ░ ░░░▓█ ▀
   ▀▀   ███▓▓▓░░░░░░░  ░▓▓░░         ░     ░▓████▓▓░░░ ░  ░░▓▓  ░   ░░▓▓▓▀
     ▄▓▄ ███▓▓▓░░░░  ▄░▀▄░░░░░░░    ░    ░▓███▓░▀▀▀██▄    ░░░     ░░░▓▓▓ ▄░▀▀▄
      ▀   ▀███▓▓▓▄▄▄ ▀▄▓▀░ ▄▄▄ ░░░░░░ ░░░▓███▓░     ▀██░ ░▓░░░ ░░░░░▓▓▓ █░   ▓█
*******************************************************************************

    Writer: Tal Aharon

    Reviewer: David.

    Date: 06.06.2023

******************************************************************************/
#include <time.h>                /* time                                      */
#include <semaphore.h>           /* sem_t, sem_init, sem_destroy              */
#include <assert.h>              /* assert                                    */
#include <stddef.h>              /* size_t, NULL                              */
#include <stdlib.h>              /* malloc, free                              */
#include <signal.h>              /* sig_atomic_t                              */
#include <pthread.h>             /* pthread_create, pthread_join              */
                                 /* pthread_mutex_init, pthread_mutex_destroy */

#include "producers_consumers.h" /* Internal API                              */
/*****************************************************************************/
#define MOD (2)
#define ROUNDS (5)
#define BUF_SIZE (10)
#define THREAD_NUM (2)
#define QUEUE_SIZE (1)
#define SEM_INIT_VAL (0)
#define PRODUCER_NUM (1)
#define M_THREAD_NUM (32)
#define M_SIX_ITEM (1000)
#define CONSUMERS_NUM (16)
#define IGNORE(X) ((void)X)
#define SHARE_WITH_THREADS (0)
/*****************************************************************************/
typedef struct list sll_t;
typedef struct sll_node *sll_iter_t;
static size_t test_buffer[M_THREAD_NUM / 2];
/*****************************************************************************/
enum consumer_producer
{
    CONSUMER = 0, PRODUCER
};
/*****************************************************************************/
typedef struct args
{
    sig_atomic_t sync;
    sll_iter_t iterator;
    void *data_structure;
    pthread_mutex_t mutex;
    sem_t consumer_semaphore;
    sem_t producer_semaphore;
} args_t;
/*****************************************************************************/
typedef struct mission_six_struct
{
    pthread_mutex_t mutex;
    pthread_cond_t cond;
    size_t consumers;
    sem_t semaphore;
    int message;
} mission_six_struct_t;
/*****************************************************************************/
typedef struct sll_node
{
    void *data;
    struct sll_node *next;
} sll_node_t;
/*****************************************************************************/
typedef struct queue
{
    size_t end;
    size_t size;
    size_t start;
    void **buffer;
} queue_t;
/*****************************************************************************/
typedef struct s_queue
{
    size_t end;
    size_t size;
    size_t start;
    sem_t dequeue_semaphore;
    sem_t enqueue_semaphore;
    pthread_mutex_t dequeue_mutex;
    pthread_mutex_t enqueue_mutex;
    void **buffer;
} s_queue_t;
/*****************************************************************************/
struct list
{
    sll_node_t *head;
    sll_node_t *tail;
};
/*****************************************************************************/
static status_t TestBuffer(void);
static void InitTestBuffer(void);
typedef void *(*routine_t)(void *);
/********************************* Mission 1 *********************************/
static void *MOneProducer(void *);
static void *MOneConsumer(void *);
static void ConsumerLock(args_t *);
static void ProducerLock(args_t *);
static void ConsumerUnLock(args_t *);
static void ProducerUnLock(args_t *);
/********************************* Mission 2 *********************************/
static void *MTwoProducer(void *);
static void *MTwoConsumer(void *);
/********************************* Mission 3 *********************************/
static void *MThreeProducer(void *);
static void *MThreeConsumer(void *);
/********************************* Mission 4 *********************************/
static void *MFourProducer(void *);
static void *MFourConsumer(void *);
/********************************* Mission 5 *********************************/
static void *MFiveProducer(void *);
static void *MFiveConsumer(void *);
/********************************* Mission 6 *********************************/
static void *MSixProducer(void *);
static void *MSixConsumer(void *);
static status_t Barrier(mission_six_struct_t *);
/**************************** Fixed size queue *******************************/
static void QueueDestroy(queue_t *);
static queue_t *QueueCreate(size_t);
static void *QueueDequeue(queue_t *);
static void QueueEnqueue(queue_t *, void *);
/********************** Thread safe Fixed size queue *************************/
static s_queue_t *QueueThreadSafeCreate(size_t);
static void QueueThreadSafeDestroy(s_queue_t *);
static void *QueueThreadSafeDequeue(s_queue_t *);
static void QueueThreadSafeEnqueue(s_queue_t *, void *);
/*************************** Singly linked list *******************************/
static sll_t *SLLCreate(void);
static void SLLDestroy(sll_t *);
static void SLLRemove(sll_iter_t);
static int SLLIsEmpty(const sll_t *);
static sll_node_t *CreateNode(void *);
static sll_iter_t SLLEnd(const sll_t *);
static void *SLLGetData(const sll_iter_t);
static sll_iter_t SLLBegin(const sll_t *);
static sll_iter_t SLLInsert(sll_iter_t iterator, void *);
static int SLLIterIsEqual(const sll_iter_t,const sll_iter_t);
static status_t RunThreads(routine_t, routine_t, void *, pthread_t *, size_t);
/*****************************************************************************/
status_t MissionOne(void)
{
    args_t args = {0};
    int buffer[BUF_SIZE] = {0};
    status_t status = PC_SUCCESS;
    pthread_t threads[THREAD_NUM] = {(pthread_t)0};
    args.sync = PRODUCER;
    args.data_structure = (void *)buffer;

    srand(time(NULL));
    status = RunThreads(MOneConsumer, MOneProducer, (void *)&args, threads, THREAD_NUM);
    return (status);
}
/*****************************************************************************/ 
status_t MissionTwo(void)
{
    args_t args = {0};
    status_t status = PC_SUCCESS;
    status_t test_status = PC_SUCCESS;
    pthread_t threads[M_THREAD_NUM] = {(pthread_t)0};

    InitTestBuffer();
    args.data_structure = (void *)SLLCreate();
    if(NULL == args.data_structure)
    {
        return (PC_FAILURE);
    }

    args.iterator = SLLBegin((sll_t *)args.data_structure);
    if(pthread_mutex_init(&args.mutex, NULL))
    {
        SLLDestroy((sll_t *)args.data_structure);
        return (PC_FAILURE);
    }

    status = RunThreads(MTwoConsumer, MTwoProducer, (void *)&args, threads, M_THREAD_NUM);

    if(PC_FAILURE == status)
    {
        SLLDestroy((sll_t *)args.data_structure);
        pthread_mutex_destroy(&args.mutex);
        return (PC_FAILURE);
    }

    if(pthread_mutex_destroy(&args.mutex))
    {
        status = PC_FAILURE;
    }

    SLLDestroy((sll_t *)args.data_structure);

    test_status = TestBuffer();
    if(PC_FAILURE == test_status)
    {
        return (PC_FAILURE);
    }

    return (status);
}
/*****************************************************************************/ 
status_t MissionThree(void)
{
    args_t args = {0};
    status_t status = PC_SUCCESS;
    status_t test_status = PC_SUCCESS;
    pthread_t threads[M_THREAD_NUM] = {(pthread_t)0};

    args.data_structure = (void *)SLLCreate();
    if(NULL == args.data_structure)
    {
        return (PC_FAILURE);
    }

    InitTestBuffer();
    args.iterator = SLLBegin((sll_t *)args.data_structure);
    if(sem_init(&args.producer_semaphore, SHARE_WITH_THREADS, SEM_INIT_VAL))
    {
        SLLDestroy((sll_t *)args.data_structure);
        return (PC_FAILURE);
    }

    if(pthread_mutex_init(&args.mutex, NULL))
    {
        SLLDestroy((sll_t *)args.data_structure);
        sem_destroy(&args.producer_semaphore);
        return (PC_FAILURE);
    }

    status = RunThreads(MThreeConsumer, MThreeProducer, (void *)&args, threads, M_THREAD_NUM);

    if(PC_FAILURE == status)
    {
        SLLDestroy((sll_t *)args.data_structure);
        sem_destroy(&args.producer_semaphore);
        pthread_mutex_destroy(&args.mutex);
        return (PC_FAILURE);
    }

    if(pthread_mutex_destroy(&args.mutex))
    {
        status = PC_FAILURE;
    }

    SLLDestroy((sll_t *)args.data_structure);
    if(sem_destroy(&args.producer_semaphore))
    {
        status = PC_FAILURE;
    }

    test_status = TestBuffer();
    if(PC_FAILURE == test_status)
    {
        return (PC_FAILURE);
    }

    return (status);
}
/*****************************************************************************/ 
status_t MissionFour(void)
{
    args_t args = {0};
    status_t status = PC_SUCCESS;
    status_t test_status = PC_SUCCESS;
    pthread_t threads[M_THREAD_NUM] = {(pthread_t)0};
    args.data_structure = (void *)QueueCreate(QUEUE_SIZE);
    if(NULL == args.data_structure)
    {
        return (PC_FAILURE);
    }

    if(sem_init(&args.producer_semaphore, SHARE_WITH_THREADS, SEM_INIT_VAL))
    {
        QueueDestroy((queue_t *)args.data_structure);
        return (PC_FAILURE);
    }

    if(sem_init(&args.consumer_semaphore, SHARE_WITH_THREADS, QUEUE_SIZE))
    {
        QueueDestroy((queue_t *)args.data_structure);
        sem_destroy(&args.producer_semaphore);
        return (PC_FAILURE);
    }

    InitTestBuffer();
    if(pthread_mutex_init(&args.mutex, NULL))
    {
        QueueDestroy((queue_t *)args.data_structure);
        sem_destroy(&args.consumer_semaphore);
        sem_destroy(&args.producer_semaphore);
        return (PC_FAILURE);
    }

    status = RunThreads(MFourConsumer, MFourProducer, (void *)&args, threads, M_THREAD_NUM);

    if(PC_FAILURE == status)
    {
        QueueDestroy((queue_t *)args.data_structure);
        sem_destroy(&args.producer_semaphore);
        sem_destroy(&args.consumer_semaphore);
        pthread_mutex_destroy(&args.mutex);
        return (PC_FAILURE);
    }

    if(pthread_mutex_destroy(&args.mutex))
    {
        status = PC_FAILURE;
    }

    QueueDestroy((queue_t *)args.data_structure);
    if(sem_destroy(&args.consumer_semaphore))
    {
        status = PC_FAILURE;
    }

    if(sem_destroy(&args.producer_semaphore))
    {
        status = PC_FAILURE;
    }

    test_status = TestBuffer();
    if(PC_FAILURE == test_status)
    {
        return (PC_FAILURE);
    }

    return (status);
}
/*****************************************************************************/ 
status_t MissionFive(void)
{
    size_t i = 0;
    long int return_value = 0;
    status_t status = PC_SUCCESS;
    status_t test_status = PC_SUCCESS;
    pthread_t threads[M_THREAD_NUM] = {(pthread_t)0};
    s_queue_t *s_queue = QueueThreadSafeCreate(QUEUE_SIZE);
    if(NULL == s_queue)
    {
        return (PC_FAILURE);
    }

    InitTestBuffer();
    for(; i < M_THREAD_NUM; ++i)
    {
        if(i % MOD)
        {
            while(pthread_create(&threads[i], NULL, MFiveConsumer, (void *)s_queue));
        }
        else
        {
            while(pthread_create(&threads[i], NULL, MFiveProducer, (void *)s_queue));
        }
    }

    for(i = 0; i < M_THREAD_NUM; ++i)
    {
        if(pthread_join(threads[i], (void *)&return_value))
        {
            QueueThreadSafeDestroy(s_queue);
            return (PC_FAILURE);
        }

        test_buffer[return_value] = return_value;
    }

    QueueThreadSafeDestroy(s_queue);
    test_status = TestBuffer();
    if(PC_FAILURE == test_status)
    {
        return (PC_FAILURE);
    }

    return (status);
}
/*****************************************************************************/ 
status_t MissionSix(void)
{
    size_t i = 0;
    status_t status = PC_SUCCESS;
    mission_six_struct_t args = {0};
    status_t return_status = PC_SUCCESS;
    pthread_t producer_thread = (pthread_t)0;
    pthread_t consumers_threads[CONSUMERS_NUM] = {(pthread_t)0};

    if(pthread_cond_init(&args.cond, NULL))
    {
        return (PC_FAILURE);
    }

    InitTestBuffer();
    args.consumers = 0;
    if(pthread_mutex_init(&args.mutex, NULL))
    {
        pthread_cond_destroy(&args.cond);
        return (PC_FAILURE);
    }

    if(sem_init(&args.semaphore, SHARE_WITH_THREADS, SEM_INIT_VAL))
    {
        pthread_mutex_destroy(&args.mutex);
        pthread_cond_destroy(&args.cond);
        return (PC_FAILURE);
    }

    while(pthread_create(&producer_thread, NULL, MSixProducer, (void *)&args));
    for(; i < CONSUMERS_NUM; ++i)
    {
        while(pthread_create(&consumers_threads[i], NULL, MSixConsumer, (void *)&args));
    }

    for(i = 0; i < CONSUMERS_NUM; ++i)
    {
        while(pthread_join(consumers_threads[i], (void *)&return_status));
        assert(return_status == PC_SUCCESS);
    }

    while(pthread_join(producer_thread, NULL));
    if(pthread_cond_destroy(&args.cond))
    {
        pthread_mutex_destroy(&args.mutex);
        sem_destroy(&args.semaphore);
        status = PC_FAILURE;
    }

    if(pthread_mutex_destroy(&args.mutex))
    {
        sem_destroy(&args.semaphore);
        status = PC_FAILURE;
    }

    if(sem_destroy(&args.semaphore))
    {
        status = PC_FAILURE;
    }

    for(i = 0; i < CONSUMERS_NUM; ++i)
    {
        if(M_SIX_ITEM != test_buffer[i])
        {
            return (PC_FAILURE);
        }
    }

    return (status);
}
/*****************************************************************************/
static status_t RunThreads
(routine_t consumer_routine, routine_t producer_routine, void *arg, pthread_t *threads, size_t size)
{
    size_t i = 0, j = 0;
    status_t return_status = PC_SUCCESS;
    for(; i < size; ++i)
    {
        if(i % MOD)
        {
            while(pthread_create(&threads[i], NULL, consumer_routine, arg));
        }
        else
        {
            while(pthread_create(&threads[i], NULL, producer_routine, arg));
        }
    }

    for(; j < size; ++j)
    {
        while(pthread_join(threads[j], (void *)&return_status));
        assert(PC_SUCCESS == return_status);
    }

    return (PC_SUCCESS);
}
/*****************************************************************************/ 
static void ConsumerLock(args_t *args)
{
    while(PRODUCER == args->sync);
}
/*****************************************************************************/
static void ProducerLock(args_t *args)
{
    while(CONSUMER == args->sync);
}
/*****************************************************************************/ 
static void ProducerUnLock(args_t *args)
{
    args->sync = CONSUMER;
}
/*****************************************************************************/
static void ConsumerUnLock(args_t *args)
{
    args->sync = PRODUCER;
}
/*****************************************************************************/ 
static void *MOneProducer(void *arg)
{
    int i = 0;
    args_t *args = (args_t *)arg;
    for(; i < BUF_SIZE; ++i)
    {
        ProducerLock(args);
        ((int *)args->data_structure)[i] = i;
        ProducerUnLock(args);
    }

    return ((void *)PC_SUCCESS);
}
/*****************************************************************************/ 
static void *MOneConsumer(void *arg)
{
    int i = 0, y = 0;
    args_t *args = (args_t *)arg;
    for(; i < BUF_SIZE; ++i)
    {
        ConsumerLock(args);
        y = ((int *)args->data_structure)[i];
        ConsumerUnLock(args);

        if(i != y)
        {
            return ((void *)PC_FAILURE);
        }
    }

    return ((void *)PC_SUCCESS);
}
/*****************************************************************************/
static void *MTwoProducer(void *arg)
{
    static size_t resource = 0;
    args_t *args = (args_t *)arg;
    while(pthread_mutex_lock(&args->mutex));

    SLLInsert(SLLBegin((sll_t *)args->data_structure), (void *)resource);
    ++resource;

    if(pthread_mutex_unlock(&args->mutex))
    {
        return ((void *)PC_FAILURE);
    }

    return ((void *)PC_SUCCESS);
}
/*****************************************************************************/
static void *MTwoConsumer(void *arg)
{
    size_t resource = 0;
    args_t *args = (args_t *)arg;
    while(pthread_mutex_lock(&args->mutex));

    while(SLLIsEmpty((sll_t *)args->data_structure))
    {
        while(pthread_mutex_unlock(&args->mutex));
        while(pthread_mutex_lock(&args->mutex));
    }

    resource = (size_t)SLLGetData(SLLBegin((sll_t *)args->data_structure));
    SLLRemove(SLLBegin((sll_t *)args->data_structure)); 
    test_buffer[resource] = resource;
    while(pthread_mutex_unlock(&args->mutex));

    return ((void *)PC_SUCCESS);
}
/*****************************************************************************/
static void *MThreeProducer(void *arg)
{
    static size_t resource = 0;
    args_t *args = (args_t *)arg;
    while(pthread_mutex_lock(&args->mutex));

   SLLInsert(SLLBegin((sll_t *)args->data_structure), (void *)resource);

    ++resource;
    while(sem_post(&(args->producer_semaphore)));
    while(pthread_mutex_unlock(&args->mutex));
    return ((void *)PC_SUCCESS);
}
/*****************************************************************************/
static void *MThreeConsumer(void *arg)
{
    size_t resource = 0;
    args_t *args = (args_t *)arg;
    while(sem_wait(&(args->producer_semaphore)));

    while(pthread_mutex_lock(&args->mutex));

    resource = (size_t)SLLGetData(SLLBegin((sll_t *)args->data_structure));
    SLLRemove(SLLBegin((sll_t *)args->data_structure));
    test_buffer[resource] = resource;

    while(pthread_mutex_unlock(&args->mutex));
    return ((void *)PC_SUCCESS);
}
/*****************************************************************************/
static void *MFourProducer(void *arg)
{
    args_t *args = (args_t *)arg;
    static size_t resource = 0;

    while(sem_wait(&(args->consumer_semaphore)));
    while(pthread_mutex_lock(&args->mutex));

    QueueEnqueue((queue_t *)args->data_structure, (void *)resource);
    ++resource;

    while(pthread_mutex_unlock(&args->mutex));
    while(sem_post(&(args->producer_semaphore)));
    return ((void *)PC_SUCCESS);
}
/*****************************************************************************/
static void *MFourConsumer(void *arg)
{
    size_t resource = 0;
    args_t *args = (args_t *)arg;
    while(sem_wait(&(args->producer_semaphore)));
    while(pthread_mutex_lock(&args->mutex));

    resource = (size_t)QueueDequeue((queue_t *)args->data_structure);
    test_buffer[resource] = resource;

    while(pthread_mutex_unlock(&args->mutex));
    while(sem_post(&(args->consumer_semaphore)));
    return ((void *)PC_SUCCESS);
}
/*****************************************************************************/
static void *MFiveProducer(void *arg)
{
    static size_t resource = 0;
    QueueThreadSafeEnqueue((s_queue_t *)arg, (void *)(resource++));
    return ((void *)0);
}
/*****************************************************************************/
static void *MFiveConsumer(void *arg)
{
    size_t resource = 0;
    resource = (long int)QueueThreadSafeDequeue((s_queue_t *)arg);
    return ((void *)(resource));
}
/*****************************************************************************/
static void *MSixProducer(void *arg)
{
    int i = 0;
    int item = M_SIX_ITEM;
    status_t status = PC_SUCCESS;
    mission_six_struct_t *args = (mission_six_struct_t *)arg;

    while(pthread_mutex_lock(&args->mutex));

    args->message = item;
    for(;i < CONSUMERS_NUM; sem_post(&args->semaphore), ++i);

    status = Barrier(args);
    return ((void *)status);
}
/*****************************************************************************/
static void *MSixConsumer(void *arg)
{
    int item = 0;
    status_t status = PC_SUCCESS;
    mission_six_struct_t *args = (mission_six_struct_t *)arg;

    while(sem_wait(&args->semaphore));
    while(pthread_mutex_lock(&args->mutex));

    item = args->message;
    test_buffer[args->consumers++] = item;

    status = Barrier(args);
    return ((void *)status);
}
/*****************************************************************************/
static status_t Barrier(mission_six_struct_t *args)
{
    if(args->consumers == CONSUMERS_NUM)
    {
        args->consumers = 0;
        if(pthread_cond_broadcast(&args->cond))
        {
            return (PC_FAILURE);
        }
    }
    else
    {
        while(pthread_cond_wait(&args->cond, &args->mutex));
    }

    while(pthread_mutex_unlock(&args->mutex));
    return (PC_SUCCESS);
}
/*****************************************************************************/
static void InitTestBuffer(void)
{
    size_t i = 0;
    for(; i < (M_THREAD_NUM / 2); ++i)
    {
        test_buffer[i] = 0;
    }
}
/*****************************************************************************/
static status_t TestBuffer(void)
{
    size_t i = 0;
    for(; i < (M_THREAD_NUM / 2); ++i)
    {
        if(i != test_buffer[i])
        {
            return (PC_FAILURE);
        }
    }

    return (PC_SUCCESS);
}
/*****************************************************************************/
static sll_t *SLLCreate(void)
{
    sll_t *list = (sll_t *)malloc(sizeof(sll_t));
    if(NULL == list)
    {
        return NULL;
    }

    list->head = CreateNode(&(list->tail));
    if(NULL == list->head)
    {
        free(list);
        return NULL;
    }

    list->head->next = NULL;
    list->tail = list->head;

    return (list);
}
/*****************************************************************************/
static void SLLDestroy(sll_t *list)
{
    sll_node_t *next = NULL;
    assert(list);
    while(list->head)
    {
        next = list->head->next;
        free(list->head);
        list->head = next;
    }

    free(list);
    list = NULL;
}
/*****************************************************************************/
static sll_iter_t SLLInsert(sll_iter_t iterator, void *data)
{
    sll_node_t *node = CreateNode(iterator->data);

    if(NULL == node)
    {
        while(iterator->next)
        {
            iterator = iterator->next;
        }

        return (iterator);
    }

    if(NULL == iterator->next)
    {
        *(sll_node_t **)(iterator->data) = node;
    }

    iterator->data = data;
    node->next = iterator->next;
    iterator->next = node;
    return (iterator);
}
/*****************************************************************************/
static void SLLRemove(sll_iter_t iterator)
{
    sll_iter_t tmp = iterator->next;
    iterator->data = tmp->data;
    iterator->next = tmp->next;
    if(NULL == iterator->next)
    {
        *((sll_node_t **)tmp->data) = iterator;
    }

    free(tmp);
    tmp = NULL;
}
/*****************************************************************************/
static int SLLIterIsEqual(const sll_iter_t iterator1,const sll_iter_t iterator2)
{
    return (iterator1 == iterator2);
}
/*****************************************************************************/
static int SLLIsEmpty(const sll_t *list)
{
    assert(list);
    return (SLLIterIsEqual(SLLBegin(list), SLLEnd(list)));
}
/*****************************************************************************/
static sll_iter_t SLLEnd(const sll_t *list)
{
    assert(list);
    return (list->tail);
}
/*****************************************************************************/
static sll_iter_t SLLBegin(const sll_t *list)
{
    assert(list);
    return (list->head);
}
/*****************************************************************************/
static sll_node_t *CreateNode(void *data)
{
    sll_node_t *node = (sll_node_t *)malloc(sizeof(sll_node_t));
    if(NULL == node)
    {
        return NULL;
    }

    node->data = data;
    return (node);
}
/*****************************************************************************/
static void *SLLGetData(const sll_iter_t iterator)
{
    return (iterator->data);
}
/*****************************************************************************/
static queue_t *QueueCreate(size_t size)
{
    size_t size_to_allocate = sizeof(queue_t) + (sizeof(void *) * size);
    queue_t *queue = (queue_t *)malloc(size_to_allocate);
    if(NULL == queue)
    {
        return (NULL);
    }

    queue->end = 0;
    queue->start = 0;
    queue->size = size;
    queue->buffer = (void **)(queue + 1);

    return (queue);
}
/*****************************************************************************/
static void QueueDestroy(queue_t *queue)
{
    assert(queue);
    free(queue);
	queue = NULL;
}
/*****************************************************************************/
static void QueueEnqueue(queue_t *queue, void *data)
{
    assert(queue);
    if(queue->size <= queue->end)
    {
        return;
    }

    queue->buffer[(queue->start + queue->end) % queue->size] = data;
    ++queue->end;
}
/*****************************************************************************/
static void *QueueDequeue(queue_t *queue)
{
    void *data = NULL;
    assert(queue);
    if(0 >= queue->end)
    {
        return (NULL);
    }

    data = queue->buffer[queue->start];
    queue->start = (queue->start + 1) % queue->size;
    --queue->end;
    return (data);
}
/*****************************************************************************/
static s_queue_t *QueueThreadSafeCreate(size_t size)
{
    size_t size_to_allocate = sizeof(s_queue_t) + (sizeof(void *) * size);
    s_queue_t *s_queue = (s_queue_t *)malloc(size_to_allocate);
    if(NULL == s_queue)
    {
        return (NULL);
    }

    s_queue->end = 0;
    s_queue->start = 0;
    s_queue->size = size;
    s_queue->buffer = (void **)(s_queue + 1);
    if(pthread_mutex_init(&s_queue->dequeue_mutex, NULL))
    {
        free(s_queue);
        return (NULL);  
    }

    if(pthread_mutex_init(&s_queue->enqueue_mutex, NULL))
    {
        pthread_mutex_destroy(&s_queue->dequeue_mutex);
        free(s_queue);
        return (NULL);
    }

    if(sem_init(&s_queue->enqueue_semaphore, SHARE_WITH_THREADS, SEM_INIT_VAL))
    {
        pthread_mutex_destroy(&s_queue->enqueue_mutex);
        pthread_mutex_destroy(&s_queue->dequeue_mutex);
        free(s_queue);
        return (NULL);
    }

    if(sem_init(&s_queue->dequeue_semaphore, SHARE_WITH_THREADS, QUEUE_SIZE))
    {
        pthread_mutex_destroy(&s_queue->enqueue_mutex);
        pthread_mutex_destroy(&s_queue->dequeue_mutex);
        sem_destroy(&s_queue->enqueue_semaphore);
        free(s_queue);
        return (NULL);
    }

    return (s_queue);
}
/*****************************************************************************/
static void QueueThreadSafeDestroy(s_queue_t *s_queue)
{
    assert(s_queue);
    sem_destroy(&s_queue->enqueue_semaphore);
    sem_destroy(&s_queue->dequeue_semaphore);
    pthread_mutex_destroy(&s_queue->enqueue_mutex);
    pthread_mutex_destroy(&s_queue->dequeue_mutex);

    free(s_queue);
    s_queue = NULL;
}
/*****************************************************************************/
static void QueueThreadSafeEnqueue(s_queue_t *s_queue, void *data)
{
    assert(s_queue);
    sem_wait(&(s_queue->dequeue_semaphore));
    pthread_mutex_lock(&s_queue->enqueue_mutex);

    s_queue->buffer[(s_queue->start + s_queue->end) % s_queue->size] = data;
    ++s_queue->end;

    pthread_mutex_unlock(&s_queue->enqueue_mutex);
    sem_post(&(s_queue->enqueue_semaphore));
}
/*****************************************************************************/
static void *QueueThreadSafeDequeue(s_queue_t *s_queue)
{
    void *data = NULL;
    assert(s_queue);

    sem_wait(&(s_queue->enqueue_semaphore));
    pthread_mutex_lock(&s_queue->dequeue_mutex);

    data = s_queue->buffer[s_queue->start];
    s_queue->start = (s_queue->start + 1) % s_queue->size;
    --s_queue->end;

    pthread_mutex_unlock(&s_queue->dequeue_mutex);
    sem_post(&(s_queue->dequeue_semaphore));
    return (data);
}
/*****************************************************************************/
