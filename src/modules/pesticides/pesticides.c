#include <stdio.h>
#include <termios.h>
#include <unistd.h>
#include <stdbool.h>
#include <errno.h>
#include <drivers/drv_hrt.h>
#include <uORB/topics/pesticides.h>
#include <px4_config.h>
#include <px4_tasks.h>
#include <px4_posix.h>

__EXPORT int pesticides_main(int argc, char *argv[]);

void pesticides_pub(void);
void usage(const char *reason);

int pesticides_main(int argc, char *argv[]) {
    PX4_INFO("pesticides pub topic");
    if(argc < 2) {
        usage("[PESTICIDES]missing command");
    }

    if(!strcmp(argv[1], "start")) {
        pesticides_pub();
    }

    return 0;
}

void pesticides_pub() {
    /*初始化数据结构体 */
    struct pesticides_s _pesticides;
    memset(&_pesticides, 0, sizeof(_pesticides));
    /* 公告主题 */
    orb_advert_t _pesticides_pub = orb_advertise(ORB_ID(pesticides), &_pesticides);

    _pesticides.opened = true;
    _pesticides.capacity = 100;
    _pesticides.duty = 80;

    PX4_INFO("pub pesticides topic");
    orb_publish(ORB_ID(pesticides), _pesticides_pub, &_pesticides);

    // while(true) {
    //     PX4_INFO("pub pesticides topic");
    //     orb_publish(ORB_ID(pesticides), _pesticides_pub, &_pesticides);
    //     // usleep(1 * 1000 * 1000);//1秒
    //     usleep(1 * 1000);//
    // }
}

void usage(const char *reason) {
    if (reason) {
        fprintf(stderr, "%s\n", reason);
    }

    fprintf(stderr, "usage: pesticides {start|stop|status} [param]\n\n");
    exit(1);
}
