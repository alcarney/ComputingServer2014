#!/usr/bin/python
import sys


from PyQt4 import QtCore, QtGui
from PyQt4.QtCore import *
from PyQt4.QtGui import *
try:
    _fromUtf8 = QtCore.QString.fromUtf8
except AttributeError:
    def _fromUtf8(s):
        return s

try:
    _encoding = QtGui.QApplication.UnicodeUTF8
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig, _encoding)


except AttributeError:
    def _translate(context, text, disambig):
        return QtGui.QApplication.translate(context, text, disambig)


# The orders class, this will display all the orders that currently need to be processed
class Ui_Orders(QtGui.QTableWidget):

    # Init function calls superclass and sets it self up
    def __init__(self):
        super(Ui_Orders,self).__init__()
        self.setupTable()

    # Sets the table up, adding columns header etc
    def setupTable(self):

        # Adding some columns and initial row
        self.setColumnCount(5)
        self.setRowCount(1)

        # Name the columns
        self.setHorizontalHeaderLabels(['Name', 'Address', 'Postcode', 'Coordinates', 'Products'])

# Order form class used to get input from user and is eventually used to display that data
class Ui_OrderForm(QtGui.QWidget):

    def __init__(self):
        super(Ui_OrderForm,self).__init__()
        self.setupForm()

    def setupForm(self):

        # Use a VBox layout
        self.formLayout = QtGui.QVBoxLayout()

        # Name
        self.nameField = QtGui.QLineEdit()
        self.formLayout.addWidget(QtGui.QLabel("Name: "))
        self.formLayout.addWidget(self.nameField)

        # Address
        self.addressField = QtGui.QLineEdit()
        self.formLayout.addWidget(QtGui.QLabel("Address: "))
        self.formLayout.addWidget(self.addressField)

        # Postcode
        self.postcodeField = QtGui.QLineEdit()
        self.formLayout.addWidget(QtGui.QLabel("Postcode: "))
        self.formLayout.addWidget(self.postcodeField)

        # Coordinates
        self.coordField = QtGui.QLineEdit()
        self.formLayout.addWidget(QtGui.QLabel("Coordinates: "))
        self.formLayout.addWidget(self.coordField)

        # Compress everything together
        self.formLayout.addStretch(1)

        # Set the layout
        self.setLayout(self.formLayout)

# The main UI class everything is controlled here
class Ui_MainWindow(QtGui.QMainWindow):

    def __init__(self):
        super(Ui_MainWindow,self).__init__()
        self.setupUI()

    def setupUI(self):

        # Window title and dimensions
        self.setWindowTitle('Axiom Enterprises - Route Logistics')
        self.setGeometry(200,200,1500,750)

        # Widgets
        orderWidget = Ui_Orders()
        formWidget = Ui_OrderForm()
        self.centreWidget = QtGui.QWidget()
        self.centreLayout = QtGui.QHBoxLayout()

        # Centre Widget layout
        self.centreLayout.addWidget(orderWidget, 2)
        self.centreLayout.addWidget(formWidget, 1)

        # Passing everything to the main window
        self.centreWidget.setLayout(self.centreLayout)
        self.setCentralWidget(self.centreWidget)

        

    def closeEvent(self, event):

        reply = QtGui.QMessageBox.question(self, '!!!WARNING!!!',
            "Are you sure to quit? All data will be lost", QtGui.QMessageBox.Yes | 
            QtGui.QMessageBox.No, QtGui.QMessageBox.No)

        if reply == QtGui.QMessageBox.Yes:
            event.accept()
        else:
            event.ignore()        
        
  
      
          
        
def main():
    app = QtGui.QApplication(sys.argv)
    window = Ui_MainWindow()
    window.show()
    sys.exit(app.exec_())


if __name__ == '__main__':
    main()
    
    
