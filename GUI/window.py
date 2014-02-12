import sys


from PyQt4 import QtCore, QtGui

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


class Ui_MainWindow(QtGui.QMainWindow):

    def __init__(self):
        super(Ui_MainWindow,self).__init__()
        self.setupUI()
    
    def setupUI(self):
        
                
        '''
Arranges how big and where the interface on the screen will be
'''

        
        self.setWindowTitle('Axiom Enterprises - Route Logistics')
        self.setGeometry(200,200,750,750)  # window size and location
        
    

        exitAction = QtGui.QAction(QtGui.QIcon('exit.png'), '&Exit', self) # exit process     
        exitAction.setShortcut('Ctrl+Q')
        exitAction.setStatusTip('Exit application')
        exitAction.triggered.connect(QtGui.qApp.quit) # possible ways to exit with a shortcut

      
        menubar = self.menuBar()
        fileMenu = menubar.addMenu('&File')  # toolbar options
        fileMenu.addAction(exitAction)  # toolbar subsections
       
        
        
        gridLayout   = QtGui.QGridLayout()
        centralWidget =     QtGui.QWidget()
    
        gridLayout.addWidget(QtGui.QPushButton("cancel"),6,6)
        gridLayout.addWidget(QtGui.QPushButton("Ok"),6,5)
        gridLayout.addWidget(QtGui.QComboBox(),0,2)
        gridLayout.addWidget(QtGui.QLineEdit(),1,0)
        gridLayout.addWidget(QtGui.QPushButton("Button 5"),1,1)
       
        self.setCentralWidget(centralWidget)
        centralWidget.setLayout(gridLayout)

        self.resize(750,750)       
      
        


        
       
        
    def closeEvent(self, event):
               
        reply = QtGui.QMessageBox.question(self, 'Message',
            "Are you sure to quit, all data will be lost?", QtGui.QMessageBox.Yes | 
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
    
    
