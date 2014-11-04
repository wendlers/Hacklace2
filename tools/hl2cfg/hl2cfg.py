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
    'fourewins': 13,
    'snake': 14,
    'jump': 15,
    'frogger': 16,
    'ttt': 17,
    'cl': 20,
    'disptest': 21,
    'usr1': 30,
    'reset': 31
}

ICONS = {
    'HL2_LOGO': 0,
    'HAPPY_SMILEY': 1,
    'SAD_SMILEY': 2,
    'SKULL': 3,
    'HEART': 4,
    'INVADER1': 5,
    'INVADER2': 6,
    'INVADER3': 7,
    'GHOST': 8,
    'FOX': 9,
    'NOTES': 11,
    'NOTE': 12,
    'GLASS': 14,
    'MOBILE': 15,
    'FLASH': 16,
    'LIGHTBULB': 17,
    'MALE': 20,
    'FEMALE': 21,
    'PHONE': 22,
    'STICKFIG': 23,
    'DIAMOND': 24,
    'CLOCK': 25,
    'BELL': 26,
    'SPACE': 32,
    'SPC1': 0xA0,
    'SPC8': 0x7F,
    ':-)': 0x01,
    ':-(': 0x02
}

ANIMS = {
    'FIRE': 1,
    'PLUG': 2,
    'ARROW': 3,
    'BALL': 4,
    'ECG': 5,
    'DROPLET': 6,
    'TRAIN': 7,
    'PONG': 8,
    'WINK': 9,
    'TNT': 10,
    'HOUSE': 11,
    'CREEPER': 12,
    'TUNNEL': 13,
    'SNOW': 14,
    'DANCER': 15,
    'FISH': 16,
    'RADAR': 17,
    'PROPELLER': 18,
    'FLATCAT': 19,
    'SUQARES': 20,
    'TETRIS': 21,
    'ROCKET': 23,
    'SPECTRUM': 24,
    'CHECKERS': 25,
    'HEADBANG': 26,
    'REVOLUTION': 31
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
            new = "\\%02X\\" % ICONS[icon]
            # print("old, new:", old, new)
            _txt = _txt.replace(old, new)

        return _txt.replace('\\\\', ' ')

    def __replace_anims(self, txt):

        _txt = txt

        for anim in ANIMS:
            # print("anim:", anim)
            old = "{{%s}}" % anim
            new = "\\%02X\\" % (ANIMS[anim] + 128)
            # print("old, new:", old, new)
            _txt = _txt.replace(old, new)

        return _txt.replace('\\\\', ' ')

    def send_conf_line(self, app_id, cfg=None, txt=None, dat=None):

        cfg_line = ''

        _cfg = cfg

        if _cfg is None and app_id == APPS['ani']:
            _cfg = '76 01'

        if _cfg is not None and txt is not None and dat is not None:
            cfg_line = '\\%02X %s\\ %s \\%s 00' % (app_id, _cfg, self.__replace_anims(self.__replace_icons(txt)), dat)
        elif _cfg is not None and txt is not None:
            cfg_line = '\\%02X %s\\ %s \\00' % (app_id, _cfg, self.__replace_anims(self.__replace_icons(txt)))
        elif _cfg is not None:
            cfg_line = '\\%02X %s' % (app_id, _cfg)
        else:
            cfg_line = '\\%02X' % app_id

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
    parser.add_argument('--listicons',
                        action="store_true",
                        help='list available icon macros')
    parser.add_argument('--listanims',
                        action="store_true",
                        help='list available animation macros')

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

        if args.listicons:
            print("Icon macros [[<macro>]]: %s" % ICONS.keys())

        if args.listanims:
            print("Animation macros {{<anim>}}: %s" % ANIMS.keys())

        if args.listicons or args.listanims:
            exit(0)

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