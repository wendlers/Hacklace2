#!/usr/bin/python

##
# The MIT License (MIT)
#
# Copyright (c) 2014 Stefan Wendler
#
# Permission is hereby granted, free of charge, to any person obtaining a copy
# of this software and associated documentation files (the "Software"), to deal
# in the Software without restriction, including without limitation the rights
# to use, copy, modify, merge, publish, distribute, sublicense, and/or sell
# copies of the Software, and to permit persons to whom the Software is
# furnished to do so, subject to the following conditions:
#
# The above copyright notice and this permission notice shall be included in
# all copies or substantial portions of the Software.
#
# THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
# IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
# FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
# AUTHORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
# LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
# OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS IN
# THE SOFTWARE.
##

__author__ = 'Stefan Wendler, sw@kaltpost.de'

import argparse
import serial
import time

DESCRIPTION = 'Configure Hacklace2 through serial line.'

APPS = {
    'ani': 0,
    'spiral': 1,
    'counter': 2,
    'gol': 3,
    'vm': 4,
    'batmon': 5,
    'freq': 6,
    'therm': 7,
    'stopwatch': 8,
    'speed': 9,
    'juke': 12,
    'disptest': 21,
    'usr1': 30,
    'reset': 31
}

ICONS = {
    'HL2': 0x00,
    ':-)': 0x01,
    ':-(': 0x02,
    'hatguy': 0x03,
    'heart': 0x04
}

ANIMS = {
    'arrow': 0x83,
    'train': 0x87
}

class HacklaceSerCom:

    def __init__(self, port, speed):

        self.sercom = serial.Serial(port=port, baudrate=speed)

    def reset(self):

        self.sercom.setDTR(False)
        time.sleep(1.5)
        self.sercom.setDTR(True)
        time.sleep(1.5)

    def send(self, data):

        # print("send:\n%s" % data)
        self.sercom.write(data)


class HacklaceDummyCom:

    def __init__(self):
        pass

    def reset(self):
        pass

    def send(self, data):
        print(data)


class HacklaceConf:

    def __init__(self, com):

        self.com = com

    def __replace_icons(self, txt):

        _txt = txt

        for icon in ICONS:
            # print("icon:", icon)
            old = "[[%s]]" % icon
            new = "\\%02x\\" % ICONS[icon]
            # print("old, new:", old, new)
            _txt = _txt.replace(old, new)

        return _txt.replace('\\\\', ' ')

    def __replace_anims(self, txt):

        _txt = txt

        for anim in ANIMS:
            # print("anim:", anim)
            old = "{{%s}}" % anim
            new = "\\%02x\\" % ANIMS[anim]
            # print("old, new:", old, new)
            _txt = _txt.replace(old, new)

        return _txt.replace('\\\\', ' ')

    def send_conf_line(self, app_id, cfg=None, txt=None, dat=None):

        cfg_line = ''

        _cfg = cfg

        if _cfg is None and app_id == APPS['ani']:
            _cfg = '76 01'

        if _cfg is not None and txt is not None and dat is not None:
            cfg_line = '\\%02x %s\\ %s \\%s 00' % (app_id, _cfg, self.__replace_anims(self.__replace_icons(txt)), dat)
        elif _cfg is not None and txt is not None:
            cfg_line = '\\%02x %s\\ %s \\00' % (app_id, _cfg, self.__replace_anims(self.__replace_icons(txt)))
        elif _cfg is not None:
            cfg_line = '\\%02x %s' % (app_id, _cfg)
        else:
            cfg_line = '\\%02x' % app_id

        self.com.reset()
        self.com.send("\eHL%s FF\\" % cfg_line.replace('\\ \\', ' '))

    def send_conf_file(self, conf_file):

        f = open(conf_file, 'r')

        self.com.reset()
        self.com.send(f.read())

        f.close()


def main():

    parser = argparse.ArgumentParser(description=('%s' % DESCRIPTION))

    parser.add_argument('--port',
                        default="/dev/ttyUSB0",
                        help='serial port')
    parser.add_argument('--speed',
                        default="2400",
                        help='serial port speed')
    parser.add_argument('--nosend',
                        action="store_true",
                        help='don\'t send any data')

    parser.add_argument('--app',
                        choices=APPS.keys(),
                        help='choose APP for which to pass in configuration')
    parser.add_argument('--cfg',
                        help='APP configuration')
    parser.add_argument('--txt',
                        help='APP text')
    parser.add_argument('--dat',
                        help='APP data')

    parser.add_argument('--cfgfile',
                        help='APP configuration from file')

    args = parser.parse_args()

    try:

        # see if args combination is valid
        if (args.app is None and args.cfgfile is None) or (args.app is not None and args.cfgfile is not None):
            raise Exception("Please give only one of the following parameters: --app or --cfgfile")
        if args.cfgfile is not None and (args.cfg is not None or args.dat is not None):
            raise Exception("No --cfg or --dat is allowed fo --cfgfile")

        com = None

        if args.nosend:
            com = HacklaceDummyCom()
        else:
            com = HacklaceSerCom(args.port, args.speed)

        cfg = HacklaceConf(com)

        if args.app is not None:
            cfg.send_conf_line(APPS[args.app], args.cfg, args.txt, args.dat)
        else:
            cfg.send_conf_file(args.cfgfile)

    except Exception as e:
        print(e)
        exit(1)

if __name__ == "__main__":
    main()