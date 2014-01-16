###########################################################################
#
#   Makefile for sample
#
###########################################################################

LIB3D = 1

#現在のディレクトリからランタイムルートディレクトリへの相対パス
ROOTDIR = ../../..

# CGROM ディレクトリ
CGROMDIR = .

# モジュール群
C_SRC  = main.c export.c battleShip.c field.c player.c game.c agtouch.c touch.c

# 追加のライブラリ
EXTRA_LIBS = $(ROOTDIR)/library/agPDevSync$(LIBPOSTFIX).lib

include $(ROOTDIR)/include/makefile.def

## Makefile ends here.
