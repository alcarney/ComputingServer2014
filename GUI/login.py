#!/usr/bin/python

import sys
from PyQt4 import QtGui, QtCore


class Ui_LoginScreen(QtGui.QWidget):

    def __init__(self):
        super(Ui_LoginScreen, self).__init__()
        self.initUI()

    def initUI(self):

        # Window title and dimensions
        self.setWindowTitle('Axiom Enterprises - Route Logistics - Login Screen')
        self.setGeometry(200,200,500,250)

        # Layout
        self.layout = QtGui.QVBoxLayout()
        buttonLayout = QtGui.QHBoxLayout()

        # Items
        self.layout.addWidget(QtGui.QLabel('Name: '))
        self.layout.addWidget(QtGui.QLineEdit())

        # Password Field
        self.layout.addWidget(QtGui.QLabel('Password: '))
        password = QtGui.QLineEdit()
        password.setEchoMode(QtGui.QLineEdit.Password)
        self.layout.addWidget(password)
        self.layout.addStretch(1)

        okButton = QtGui.QPushButton('OK')
        okButton.clicked.connect(self.attemptLogin)
        quitButton = QtGui.QPushButton('Quit')
        quitButton.clicked.connect(self.closeEvent)

        buttonLayout.addWidget(okButton)
        buttonLayout.addWidget(quitButton)

        self.layout.addLayout(buttonLayout)
        self.setLayout(self.layout)

    def attmeptLogin(self):
        # Open the file containing the accounts
        source = open('accounts.txt', 'r')

        # Get the data from the file
        raw_data = source.read().split('\n')
        accounts = []
        # Load the accounts
        for i in raw_data:
            accounts.append([i.split(',')])

        print accounts


    def closeEvent(self):
        QtCore.QCoreApplication.instance().quit()


def main():
    print sys.argv

    app = QtGui.QApplication(sys.argv)

    window = Ui_LoginScreen()
    window.show()
    sys.exit(app.exec_())
    return [1,2,3]

if __name__=="__main__":
    main()
