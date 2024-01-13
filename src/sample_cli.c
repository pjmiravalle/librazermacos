#include<stdio.h>
#include "razerdevice.h"
#include "razerkbd_driver.h"
#include "razermousemat_driver.h"

int main(int argc, const char * argv[]) {
    RazerDevices allDevices = getAllRazerDevices();
    RazerDevice *razerDevices = allDevices.devices;

    printf("%d Razer device(s) found:\n", allDevices.size);

    for (int i = 0; i < allDevices.size; i++) {
        RazerDevice device = razerDevices[i];
        printf("%#06x\n", device.productId);

        // Testing out the blackwidow v3 pro changes by switching to wave
        if (device.productId == 0x025A)
        {
            printf("Found blackwidow v3 pro keyboard (wired)\n");
            razer_attr_write_mode_wave(device.usbDevice, "1", 0, 0x90);
        }

        if (device.productId == 0x0c06)
        {
            printf("Found goliathus 3xl mouse mat!\n");
            printf("Setting mode to static\n");

            uint8_t rgb[3];
            rgb[0] = 0;
            rgb[1] = 255;
            rgb[2] = 0;

            char *buf = (char *) rgb;

            // razer_mouse_mat_attr_write_mode_spectrum(device.usbDevice, "1", 0);
            razer_mouse_mat_attr_write_mode_static(device.usbDevice, buf, 3);
        }
    }

    closeAllRazerDevices(allDevices);
    return 0;

}
