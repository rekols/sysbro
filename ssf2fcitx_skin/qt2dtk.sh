#!/bin/bash
# Bash script for converting source files in a Qt project
# to those compatible with DTK (Deepin Tool Kit)
# Basically, a conversion of class name from QXXX to DXXX is performed
# Manual modification is generally required to correct syntax etc.

SRC_FILE_TYPE=".cpp .c .h .ui"

CONVERSION_LIST="
QApplication/DApplication
QFileDialog/DFileDialog
QWindow/DWindow
QMainWindow/DMainWindow
QButton/DPushButton
QDialog/DDialog
QFontComboBox/DFontComboBox
QLabel/DLabel
QLineEdit/DLineEdit
QListView/DListView
QScrollBar/DScrollBar
QSlider/DSlider
QSpinner/DSpinner
QTextEdit/DTextEdit
<DMainWindow>/<dmainwindow.h>
<DLabel>/<dlabel.h>
<DDialog>/<ddialog.h>
DButtonGroup/QButtonGroup
DDialogButtonBox/QDialogButtonBox
<ddialogbuttonbox.h>/<QDialogButtonBox>
<QtWidgets\/DApplication>/<QtWidgets\/QApplication>
"

function listFileRecursively
{
    # Detect for "tree" command
    tree > /dev/null 2>&1
    if [ $? -ne 0 ]; then
        echo "Command 'tree' not found. Please install package 'tree' first."
        exit 0
    fi
    tree -i -f --noreport $1
}

function isQtClassFile
{
    classFileName=$(echo $1 | grep -i "\\.h$")
    if [ -z $classFileName ]; then return 0; fi
    uiFileName=${classFileName/.h/.ui}
    if [ -f $uiFileName ]; then
        echo "true"
    else
        echo "false"
    fi
}

SOURCE_DIR=$1
if [ -z $SOURCE_DIR ]; then
    proFile=$(ls *.pro 2>/dev/null)
    if [ -z $proFile ]; then
        echo "Please specify a source directory!"
        exit 0
    else
        # Use current directory as source directory
        SOURCE_DIR=$(pwd)
    fi
fi

TARGET_DIR=$2
if [ -z "$TARGET_DIR" ]; then
    # Do conversion in place
    TARGET_DIR=$SOURCE_DIR
else
    cp -Rf $SOURCE_DIR $TARGET_DIR
fi


# Get source file list
SRC_FILE_FILTER=${SRC_FILE_TYPE//\./\\.}
SRC_FILE_FILTER=${SRC_FILE_FILTER// /$|}
SRC_FILE_FILTER=$SRC_FILE_FILTER'$'
srcFiles=$(listFileRecursively $TARGET_DIR/ | grep -i -E "$SRC_FILE_FILTER")


# Do conversion for each source file found
for srcFile in $srcFiles; do

    # Do general conversions
    for replacement in $CONVERSION_LIST; do
	sed -i s/$replacement/ $srcFile
    done

    # Additional remarks
    ret=$(isQtClassFile "$srcFile")
    if [ "$ret" == "true" ]; then
        # Using namespace Dtk
        bodyStart=$(grep -n -E "class.+:|class.+Ui_" $srcFile)
        bodyStartLineNumber=${bodyStart%%:*}
        sed -i "$bodyStartLineNumber""iusing namespace Dtk::Widget;\n" $srcFile
    fi

done

# Add an config line for the project file
proFiles=$(ls $TARGET_DIR/*.pro)
for proFile in $proFiles; do
    echo "
CONFIG += link_pkgconfig
PKGCONFIG += dtkwidget
" >> $proFile
done

echo "Finished conversion!"
exit 0
