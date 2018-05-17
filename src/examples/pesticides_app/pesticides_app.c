#include <px4_config.h>
#include <px4_tasks.h>
#include <px4_posix.h>
#include <unistd.h>
#include <stdio.h>
#include <poll.h>
#include <string.h>
#include <math.h>

#include <uORB/uORB.h>
#include <uORB/topics/pesticides.h>


__EXPORT int pesticides_app_main(int argc, char *argv[]);

int pesticides_app_main(int argc, char *argv[]) {
    PX4_INFO("Hello pesticides!");

    /* subscribe to rw_uart_sonar topic */
    int pesticides_fd = orb_subscribe(ORB_ID(pesticides));
    // printf("pesticides_fd = %d \n", pesticides_fd);

    /*设置以一秒钟接收一次，并打印出数据*/
    // orb_set_interval(pesticides_fd, 1000);
    // bool updated;

    struct pesticides_s _pesticides;
    memset(&_pesticides, 0, sizeof(_pesticides));
    //公告主题 测试
    orb_advert_t pesticides_pub = orb_advertise(ORB_ID(pesticides), &_pesticides);
    _pesticides.opened = true;
    _pesticides.capacity = 90;
    _pesticides.duty = 50;
    //发布主题数据
    orb_publish(ORB_ID(pesticides), pesticides_pub, &_pesticides);

    struct pesticides_s data_copy;
    orb_copy(ORB_ID(pesticides), pesticides_fd, &data_copy);
    printf("[pesticides_app] pesticide data:\t%d\t%d\t%d\n",
        data_copy.opened, data_copy.capacity, data_copy.duty);


    // //订阅主题
    // /* one could wait for multiple topics with this technique, just using one here */
    // struct pollfd fds[] = {
    //     { .fd = pesticides_fd,   .events = POLLIN },
    // };
    //
    //  int error_counter = 0;
    //  for (int i = 0; i < 5; i++) {
    //     /* wait for sensor update of 1 file descriptor for 1000 ms (1 second) */
    //     int poll_ret = poll(fds, 1, 1000);
    //
    //     printf("error_counter = %d, poll_ret = %d \n", error_counter, poll_ret);
    //
    //     /* handle the poll result */
    //     if (poll_ret == 0) {
    //         /* this means none of our providers is giving us data */
    //         printf("[pesticides_app] Got no data within a second\n");
    //
    //     } else if (poll_ret < 0) {
    //         /* this is seriously bad - should be an emergency */
    //         if (error_counter < 10 || error_counter % 50 == 0) {
    //             /* use a counter to prevent flooding (and slowing us down) */
    //             printf("[pesticides_app] ERROR return value from poll(): %d\n"
    //                    , poll_ret);
    //         }
    //
    //         error_counter++;
    //
    //     } else {
    //
    //         if (fds[0].revents & POLLIN) {
    //             /* obtained data for the first file descriptor */
    //             struct pesticides_s pesticide;
    //             memset(&pesticide, 0, sizeof(pesticide));
    //             /* copy sensors raw data into local buffer */
    //             orb_copy(ORB_ID(pesticides), pesticides_fd, &pesticide);
    //             printf("[pesticides_app] pesticide data:\t%d\t%d\t%d\n",
    //                    pesticide.opened, pesticide.capacity, pesticide.duty);
    //         }
    //
    //         /* there could be more file descriptors here, in the form like:
    //          * if (fds[1..n].revents & POLLIN) {}
    //          */
    //     }
    // }

    return 0;
}
