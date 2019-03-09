/*
 * Copyright (C) 2013 The Android Open Source Project
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

package com.example.ieeeremotecaregiver;

import java.util.HashMap;

/**
 * This class includes a small subset of standard GATT attributes for demonstration purposes.
 */
public class SampleGattAttributes {
    private static HashMap<String, String> attributes = new HashMap();
    public static String CLIENT_CHARACTERISTIC_CONFIG = "00002902-0000-1000-8000-00805f9b34fb";

    public static String HM10_DATA_SERVICE= "0000ffe0-0000-1000-8000-00805f9b34fb";
    public static String HM10_DEVICE_SERVICE = "00001800-0000-1000-8000-00805f9b34fb";
//
//    public static String HM10_DATA_CHARACTERISTIC = "0000ffe1-0000-1000-8000-00805f9b34fb";
    //intential error in id so data doesnt get parsed
    public static String HM10_DATA_CHARACTERISTIC = "0000bbb1-0000-1000-8000-00805f9b34fb";

    public static String HM10_DEVICE_CHARACTERISTIC = "00002a00-0000-1000-8000-00805f9b34fb";



    static {
        attributes.put(HM10_DATA_SERVICE, "HM10 Data Service");
        attributes.put(HM10_DEVICE_SERVICE, "HM10 Device Information Service");

        attributes.put(HM10_DATA_CHARACTERISTIC, "HM10 Data Characteristic");
        attributes.put(HM10_DEVICE_CHARACTERISTIC, "Manufacturer Name String");
    }

    public static String lookup(String uuid, String defaultName) {
        String name = attributes.get(uuid);
        return name == null ? defaultName : name;
    }
}
