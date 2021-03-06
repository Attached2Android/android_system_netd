/*
 * Copyright (C) 2008 The Android Open Source Project
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *      http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#ifndef _SOFTAP_CONTROLLER_H
#define _SOFTAP_CONTROLLER_H

#include <linux/in.h>
#include <net/if.h>

#include <sysutils/SocketListener.h>
#include <sys/socket.h>

#define SOFTAP_MAX_BUFFER_SIZE	4096
#define AP_BSS_START_DELAY	200000
#define AP_BSS_STOP_DELAY	500000
#define AP_SET_CFG_DELAY	500000
#define AP_DRIVER_START_DELAY	800000
#define AP_CHANNEL_DEFAULT	6

class SoftapController {
public:
    SoftapController();
    virtual ~SoftapController();

    int startSoftap(bool global_ctrl_iface = false, SocketClient *socketClient = NULL, const char *iface = NULL);
    int stopSoftap();
    bool isSoftapStarted();
    int setSoftap(int argc, char *argv[]);
    int fwReloadSoftap(int argc, char *argv[]);
private:
    SocketClient *mSocketClient;
#ifdef LIBWPA_CLIENT_EXISTS
    pthread_t mThread;
    int mThreadErr;
    bool mHostapdFlag;
#endif
    pid_t mPid;
    bool generatePsk(char *ssid, char *passphrase, char *psk);
#ifdef LIBWPA_CLIENT_EXISTS
    static void *threadStart(void *obj);
#endif
};

#endif
