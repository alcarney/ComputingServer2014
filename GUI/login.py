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

    def attemptLogin(self):
        # Open the file containing the accounts
        # TODO: Make that the file is written in plain binary 
        # so that its not human readable

        source = open('accounts.txt', 'r')

        # Get the data from the file
        raw_data = source.read().split('\n')
        source.close()

        # Load the accounts
        accounts = []

        for i in raw_data:
            accounts.append(i.split(','))

        #print accounts

        # Get the login attempt
        name = (self.layout.itemAt(1).widget().text())
        password = (self.layout.itemAt(3).widget().text())

        # Clear the input fields
        self.layout.itemAt(1).widget().clear()
        self.layout.itemAt(3).widget().clear()

        #print name 
        #print password
        # TODO: If one of the fields are left blank show msg to user 
        # saying which one is needed and highlight it with a red border
        
        # Check to see if account exists
        accountExists = False
        accountIndex = 0
        j = 0

        for i in accounts:
            if i[0] == name:
                accountExists = True
                accountIndex = j
            j += 1
        #print accountExists
        #print accountIndex

        # If account exists check if password is correct
        if accountExists == True:
            if password == accounts[accountIndex][1]:
                print "Login Succeeded"
            else:
                print "Login Failed: Invalid Password"
        else:
            print "Login Failed: Invalid Username"


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
