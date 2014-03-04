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

class Ui_FormEntry():

        def __init__(self):
            pass
        def setup(self):
            
            list1 = ['select',
            'Dell1',
            'Dell2',
            'Dell3']
    
            list2 = ['1','2','3','4','5','6','7','8','9','10','11','12','13','14','15']
            

            dataLayout = QtGui.QHBoxLayout()
            # Each of These Contain the elements of the form, eg name,address etc
            formElementName = QtGui.QVBoxLayout()
            formElementAddress = QtGui.QVBoxLayout()
            formElementPostcode = QtGui.QVBoxLayout()
            formElementCoords = QtGui.QVBoxLayout()
            formElementProd1 = QtGui.QVBoxLayout()
            formElementProd2 = QtGui.QVBoxLayout()
            formElementProd3 = QtGui.QVBoxLayout()
                    
            formElementName.addWidget(QtGui.QLabel("Customer Name"))
            self.customer = QtGui.QLineEdit()
            formElementName.addWidget(self.customer)
            
            formElementAddress.addWidget(QtGui.QLabel("First line of address"))
            self.address = QtGui.QLineEdit()
            formElementAddress.addWidget(self.address)
            
            formElementPostcode.addWidget(QtGui.QLabel("Postcode"))
            self.Postcode = QtGui.QLineEdit()
            formElementPostcode.addWidget(self.Postcode)
            
            formElementCoords.addWidget(QtGui.QLabel("Coordinates"))
            self.coordinates = QtGui.QLineEdit()
            formElementCoords.addWidget(self.coordinates)
            
            formElementProd1.addWidget(QtGui.QLabel("Product 1"))
            self.Product1 = QtGui.QComboBox()
            formElementProd1.addWidget(self.Product1)
            self.Product1.addItems(list1)

            
            formElementProd1.addWidget(QtGui.QLabel("Quantity"))
            self.Prod1Quantity = QtGui.QComboBox()
            formElementProd1.addWidget(self.Prod1Quantity)
            self.Prod1Quantity.addItems(list2)
            
            formElementProd2.addWidget(QtGui.QLabel("Product 2"))
            self.Product2 = QtGui.QComboBox()
            formElementProd2.addWidget(self.Product2)
            self.Product2.addItems(list1)
            
            formElementProd2.addWidget(QtGui.QLabel("Quantity"))
            self.Prod2Quantity = QtGui.QComboBox()
            formElementProd2.addWidget(self.Prod2Quantity)
            self.Prod2Quantity.addItems(list2)
            
            formElementProd3.addWidget(QtGui.QLabel("Product 3"))
            self.Product3 = QtGui.QComboBox()
            formElementProd3.addWidget(self.Product3)
            self.Product3.addItems(list1)
            
            formElementProd3.addWidget(QtGui.QLabel("Quantity"))
            self.Prod3Quantity = QtGui.QComboBox()
            formElementProd3.addWidget(self.Prod3Quantity)
            self.Prod3Quantity.addItems(list2)


            #self.address.setObjectName("host")
            #self.Postcode.setObjectName("host2")
            #self.customer.setObjectName("host3")

        
      

            dataLayout.addLayout(formElementName)
            dataLayout.addLayout(formElementAddress)
            dataLayout.addLayout(formElementPostcode)
            dataLayout.addLayout(formElementCoords)
            dataLayout.addLayout(formElementProd1)
            dataLayout.addLayout(formElementProd2)
            dataLayout.addLayout(formElementProd3)
         

            return dataLayout
        
       
                   
            
class Ui_MainWindow(QtGui.QMainWindow):

    def __init__(self):
        super(Ui_MainWindow,self).__init__()
        self.setupUI()

    def setupUI(self):

        # Window appearance 
        self.setWindowTitle('Axiom Enterprises - Route Logistics')
        self.setGeometry(200,200,750,750)  
        
        # The main content goes here
        self.centreWidget = QtGui.QWidget()
        mainLayout = QtGui.QVBoxLayout()

        # Bottom Buttons
        bottomDock = QtGui.QDockWidget()        #Used to place the buttons
        bottomDockWidget = QtGui.QWidget()      # Contains the buttons
        buttonLayout = QtGui.QHBoxLayout()


        menubar = self.menuBar()
        fileMenu = menubar.addMenu('&File')  # toolbar options
       
        
        # These are used to create the overall look of the screen


        l = Ui_FormEntry()
        mainLayout.addLayout(l.setup())
        mainLayout.addStretch(0.5)

        # ------------------- Bottom Dock ----------------------------

        # Building the layout

        self.addOrderButton = QtGui.QPushButton("Add Order")

        buttonLayout.addWidget(self.addOrderButton)
        buttonLayout.addStretch(1)
        self.OkButton = QtGui.QPushButton("Ok")
        buttonLayout.addWidget(self.OkButton)
        self.CancelButton = QtGui.QPushButton("cancel")
        buttonLayout.addWidget(self.CancelButton)

        # Adding the bottom dock to screen
        bottomDockWidget.setLayout(buttonLayout)
        bottomDock.setWidget(bottomDockWidget)
        bottomDock.setFeatures(QDockWidget.NoDockWidgetFeatures)
        self.addDockWidget(Qt.BottomDockWidgetArea, bottomDock)


        # Adding the main content to the screen
        self.centreWidget.setLayout(mainLayout)
        self.setCentralWidget(self.centreWidget)



        
        # Adding functionality to the screen
        exitAction = QtGui.QAction(QtGui.QIcon('exit.png'), '&Exit', self) # exit process     
        exitAction.setShortcut('Ctrl+Q')
        exitAction.setStatusTip('Exit application')
        exitAction.triggered.connect(QtGui.qApp.quit) # possible ways to exit with a shortcut
        fileMenu.addAction(exitAction)  # Exit Option in file menu

        # Naming the Line edit Widgets for differentiability
        self.create_connections()
        

    # Add a new row to the form
    def addEntry(self):

        # Gain control over the central widget again
        self.centreWidget = self.centralWidget()

        # Gain control over the central widget's layout again
        Layout = self.centreWidget.layout()

        # Create a new form entry
        l = Ui_FormEntry()

        # Append the entry to the layout
        Layout.insertLayout(Layout.count()+1,l.setup())

        # Add the new layout to the central widget
        self.centreWidget.setLayout(Layout)

        # Pass the new widget back to the window
        self.setCentralWidget(self.centreWidget)

    def create_connections(self):
        self.addOrderButton.clicked.connect(self.addEntry)
        self.CancelButton.clicked.connect(self.closeGUI) 
        #self.OkButton.clicked.connect(self.button_click)
#####################################################################
    '''
    def button_click(self):
               
        shost = str(self.coordinates.text())
        shost2 = str(self.Postcode.text())
        shost3 = str(self.customer.text())
        self.coordinateslist.append(shost)
        shipping = [shost3,shost2,shost]
        print shipping
	'''	
######################################################################     
    def append():
        pass
    def closeGUI(self):
        reply = QtGui.QMessageBox.question(self, '!!!WARNING!!!',
            "Are you sure to quit? All data will be lost", QtGui.QMessageBox.Yes | 
            QtGui.QMessageBox.No, QtGui.QMessageBox.No)

        if reply == QtGui.QMessageBox.Yes:
            QtCore.QCoreApplication.instance().quit()
        else:
            pass       
        
        
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
    
    
