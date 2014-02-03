#!/usr/bin/python2.7

import sys
from PyQt4 import QtGui

def main():

    app = QtGui.QApplication(sys.argv)

    w = QtGui.QWidget()
    w.resize(250,150)
    w.move(300,300)
    w.setWindowTitle('Simple Window')
    w.show()

    sys.exit(app.exec_())


