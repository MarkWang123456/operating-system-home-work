#include <linux/module.h>
#include <linux/kernel.h>
#include <linux/time.h>     

extern long long ts; 

int init_module(void) {
    long long current_ts;
    long long age_seconds;
    long long age_years;
    
    // 檢查 date2timestamp.c 是否已成功載入並匯出 ts
    if (ts == 0) {
        printk(KERN_ERR "myage: Failed to get timestamp (ts). Is date2timestamp loaded?\n");
        return -EINVAL; 
    }

    current_ts = ktime_get_real_seconds();
    age_seconds = current_ts - ts;
    
    // 365.25 * 24 * 60 * 60 = 31557600 秒
    age_years = age_seconds / 31557600LL;

    printk(KERN_INFO "myage inserted successfully!\n");
    printk(KERN_INFO "Birth Timestamp (from date2timestamp): %lld\n", ts);
    printk(KERN_INFO "Current Timestamp: %lld\n", current_ts);
    printk(KERN_INFO "Age in seconds: %lld\n", age_seconds);
    printk(KERN_INFO "Calculated Age: %lld years\n", age_years);

    return 0;
}

void cleanup_module(void) {
    printk(KERN_INFO "myage remove successfully!\n");
}

MODULE_LICENSE("GPL");
MODULE_AUTHOR("<MarkWang>");
MODULE_DESCRIPTION("oslab5: myage module calculates age from timestamp");