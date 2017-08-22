        /* For ZwQueryObject() */
#include <Ntifs.h>

extern int _printk(const char *func, const char *fmt, ...)
#define printk(format, ...)   \
    _printk(__FUNCTION__, format, __VA_ARGS__)

void print_object_handle(HANDLE h)
{
        PUBLIC_OBJECT_TYPE_INFORMATION object_type_information;

        status = ZwQueryObject(h, ObjectTypeInformation, &object_type_information, sizeof(object_type_information), NULL);
        if (!NT_SUCCESS(status)) {
                printk(KERN_WARN "ZwQueryObject: Cannot query object, status = %x, path = %s\n", status, path);
		return;
        }
        printk(KERN_INFO "ZwQueryObject succeeded. path: %s Type name: %S\n", path, object_type_information.TypeName.Buffer);
}

