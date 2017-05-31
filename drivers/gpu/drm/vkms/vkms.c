#include "vkms.h"

#define DRIVER_NAME	"vkms"
#define DRIVER_DESC	"Virtual KMS provider"
#define DRIVER_DATE	"20170534"
#define DRIVER_MAJOR	1
#define DRIVER_MINOR	0


static struct drm_driver vkms_driver = {
	.name = DRIVER_NAME,
	.desc = DRIVER_DESC,
	.date = DRIVER_DATE,
	.major = DRIVER_MAJOR,
	.minor = DRIVER_MINOR,
};

static struct drm_device *vkms_device;

static int __init vkms_init(void)
{
	int ret = 0;
	vkms_device = drm_dev_alloc(&vkms_driver, NULL);
	if (IS_ERR(vkms_device)) {
		ret = PTR_ERR(vkms_device);
		return ret;
	}

	ret = drm_dev_register(vkms_device, 0);
	if (ret) {
		drm_dev_unref(vkms_device);
		return ret;
	}
	pr_info("Initialising Virtual KMS driver\n");

	return ret;
}


static void __exit vkms_exit(void)
{
	drm_dev_unregister(vkms_device);
	drm_dev_unref(vkms_device);
	pr_info("Removing Virtual KMS driver\n");
}

module_init(vkms_init);
module_exit(vkms_exit);

MODULE_AUTHOR("Bram Vlerick");
MODULE_DESCRIPTION(DRIVER_DESC);
MODULE_LICENSE("GPL");
