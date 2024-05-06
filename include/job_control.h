/*
** EPITECH PROJECT, 2024
** 42sh
** File description:
** job_control
*/

#ifndef JOB_CONTROL_H_
    #define JOB_CONTROL_H_

    #include <sys/types.h>

    typedef enum plane_s {
        FG,
        BG
    }plane_t;

    typedef struct job_process_s {
        int id;
        pid_t pid;
        plane_t plane;
    }job_process_t;

#endif /* !JOB_CONTROL_H_ */
