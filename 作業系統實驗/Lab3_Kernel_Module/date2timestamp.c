#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/time.h>
#include <linux/stat.h>
#include <linux/errno.h>
#include <linux/timekeeping.h>

int y = 2025;
int m = 12;
int d = 25;
long long ts = 0; 

module_param(y, int, 0);
module_param(m, int, 0);
module_param(d, int, 0);
MODULE_PARM_DESC(y, "Birth Year");
MODULE_PARM_DESC(m, "Birth Month");
MODULE_PARM_DESC(d, "Birth Day");

long long date_to_timestamp(int y,int m,int d) {
    struct tm t = {0};
    time64_t calculated_ts;
    if (y < 1970 || m < 1 || m > 12 || d < 1 || d > 31) {
        return -1;
    };

    t.tm_year = y - 1900;
    t.tm_mon = m - 1;
    t.tm_mday = d;
    
    calculated_ts = mktime64(y, m, d, 
        0, // Hour
        0, // Minute
        0  // Second
    );

    if(calculated_ts < 0){
        return -1;
    }else{
        return calculated_ts;
    }
}

int init_module(void) {
    ts = date_to_timestamp(y,m,d);
    if(ts>0){
        printk(KERN_INFO "date2timestamp inserted successfully! ts=%lld\n", ts);
        printk(KERN_INFO "date2timestamp insert successfully!\n");
        return 0;
    }else{
        printk(KERN_ERR "date2timestamp: Failed to convert date %d/%d/%d to timestamp.\n", y, m, d);
        return -1;
    }
}

void cleanup_module(void) {
    printk(KERN_INFO "date2timestamp remove successfully!\n");
}

// 使得其它模組可以使用它們 
EXPORT_SYMBOL(ts);

MODULE_LICENSE("GPL");
MODULE_AUTHOR("<MarkWang>");
MODULE_DESCRIPTION("homework: date2timestamp");
