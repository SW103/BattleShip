###########################################################################
#
#   Makefile for sample
#
###########################################################################

#現在のディレクトリからランタイムルートディレクトリへの相対パス
ROOTDIR = ../../..

# CGROM ディレクトリ
CGROMDIR = .

# モジュール群
C_SRC  = main.c export.c battleShip.c field.c player.c game.c agtouch.c touch.c

include $(ROOTDIR)/include/makefile.def

## Makefile ends here.
