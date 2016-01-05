#!/usr/bin/env python
'''
    eDomitory
    Copyright (C) 2015-2016  Samhjn

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
'''
import requests
import serial

# Global Settings
server_addr = "http://127.0.0.1:8000/api/"
arduino_port = "/dev/ttyUSB0"
arduino_rate = 9600


class Server:
    '''
    Communicate with server via this class
    '''
    server_addr = ""
    server_token = ""

    def __init__(self, server_addr):
        self.server_addr=server_addr

    def login(self):
        pass

    def get(self, url):
        r = requests.post(self.server_addr+url)
        try:
            return r.json()
        except:
            return {'status': -1}


class Client:
    '''
    Manage client info
    '''
    status = 0
    id = 0
    role = 0
    server = classmethod
    arduino = classmethod

    def __init__(self, id, role, server, arduino):
        self.id = id
        self.role = role
        self.server = server
        self.arduino = arduino

    def update(self, status):
        self.status = status
        result = self.notify()
        return result

    def notify(self):
        result = self.server.get('client/notify/?id='+str(self.id)+'&status='+str(self.status))
        return result

    def trigger(self, arduino):
        result = arduino.msg(id, self.status)
        return result


class Arduino:
    '''
    Send and recieve information via Arduino
    '''
    ser = classmethod

    def __init__(self, port,rate):
        self.ser = serial.Serial(port, rate, timeout=1)

    def msg(self, id, status):
        self.ser.write(id)
        self.ser.write(3)
        self.ser.write(0)

    def read(self):
        # TODO
        pass

#TODO: Control of Raspberry Pi