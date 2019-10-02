#!/bin/sh

#
# make-bindist_win32.sh -- Make a binary distribution for the Windows GTK3 port.
#
# Written by
#  Marco van den Heuvel <blackystardust68@yahoo.com>
#  Greg King <gregdk@users.sf.net>
#  Bas Wassink <b.wassink@ziggo.nl>
#
# This file is part of VICE, the Versatile Commodore Emulator.
# See README for copyright notice.
#
#  This program is free software; you can redistribute it and/or modify
#  it under the terms of the GNU General Public License as published by
#  the Free Software Foundation; either version 2 of the License, or
#  (at your option) any later version.
#
#  This program is distributed in the hope that it will be useful,
#  but WITHOUT ANY WARRANTY; without even the implied warranty of
#  MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
#  GNU General Public License for more details.
#
#  You should have received a copy of the GNU General Public License
#  along with this program; if not, write to the Free Software
#  Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA
#  02111-1307  USA.
#
# Usage: make-bindist.sh <strip> <vice-version> <--enable-arch> <zip|nozip> <x64-included> <top-srcdir> <cpu> <abs-top-builddir> <cross> <objdump> <compiler>
#                         $1      $2             $3              $4          $5             $6           $7    $8                 $9      $10       $11
#

STRIP=$1
VICEVERSION=$2
ENABLEARCH=$3
ZIPKIND=$4
X64INC=$5
TOPSRCDIR=$6
CPU=$7
TOPBUILDDIR=$8
CROSS=$9

shift
OBJDUMP=$9

shift
COMPILER=$9


# Try to get the SVN revision
#echo "Trying to get SVN revision"
SVN_SUFFIX=""
svnrev_string=`svnversion $TOPSRCDIR`
if test "$?" != "0"; then
    #echo "No svnversion found"
    # nop:
    :
else
    # Choose the second number (usually higher) if it exists; drop letter suffixes.
    svnrev=`echo "$svnrev_string" | sed 's/^\([0-9]*:\)*\([0-9]*\)*.*/\2/'`
    #echo "svnrev string: $svnrev"
    # Only a number is extracted.
    if test -n "$svnrev"
        then SVN_SUFFIX="-r$svnrev"
    fi
fi


get_dll_deps()
{
  for j in $BUILDPATH/*.dll; do
    dlls=`$OBJDUMP -p $j | gawk '/^\\tDLL N/{print $3;}'`
    for i in $dlls
    do test -e $dlldir/$i&&cp -u $dlldir/$i $BUILDPATH
    done
  done
}


if test x"$CPU" = "xx86_64" -o x"$CPU" = "xamd64"; then
  WINXX="win64"
else
  WINXX="win32"
fi

if test x"$X64INC" = "xyes"; then
    X64FILE="x64"
else
    X64FILE=""
fi


EMULATORS="$X64FILE x64sc xscpu64 x64dtv x128 xcbm2 xcbm5x0 xpet xplus4 xvic vsid"
CONSOLE_TOOLS="c1541 cartconv petcat"
EXECUTABLES="$EMULATORS $CONSOLE_TOOLS"

unset CONSOLE_TOOLS EMULATORS X64FILE X64INC CPU svnrev_string

for i in $EXECUTABLES; do
  if [ ! -x $TOPBUILDDIR/src/$i.exe ]; then
    echo 'Error: executable files not found; do a "make" first.'
    exit 1
  fi
done


GTK3NAME="GTK3VICE"
BUILDPATH="$TOPBUILDDIR/$GTK3NAME-$VICEVERSION-$WINXX$SVN_SUFFIX"
#echo "BUILDPATH = $BUILDPATH"


echo "Removing an old $BUILDPATH ..."
rm -r -f $BUILDPATH

echo "Generating a $WINXX GTK3 port binary distribution..."
mkdir $BUILDPATH

for i in $EXECUTABLES; do
  cp $TOPBUILDDIR/src/$i.exe $BUILDPATH
  $STRIP $BUILDPATH/$i.exe
done

if test x"$CROSS" != "xtrue"; then

# The following lines assume that this script is run by MSYS2.
  cp `ntldd -R $BUILDPATH/x64sc.exe|gawk '/\\\\bin\\\\/{print $3;}'|cygpath -f -` $BUILDPATH
  cd $MINGW_PREFIX
  cp bin/lib{croco-0.6-3,lzma-5,rsvg-2-2,xml2-2}.dll $BUILDPATH
  cp --parents lib/gdk-pixbuf-2.0/2.*/loaders.cache lib/gdk-pixbuf-2.0/2.*/loaders/libpixbufloader-{png,svg,xpm}.dll $BUILDPATH
  # GTK3 accepts having only scalable icons,
  # which reduces the bindist size considerably.
  cp --parents -a share/icons/Adwaita/{index.*,scalable} $BUILDPATH
  rm -r $BUILDPATH/share/icons/Adwaita/scalable/emotes
  cp --parents share/icons/hicolor/index.theme $BUILDPATH
  cp --parents share/glib-2.0/schemas/gschemas.compiled $BUILDPATH
  cp bin/gspawn-win??-helper*.exe $BUILDPATH
  cd - >/dev/null
else

# The following lines assume a cross compiler,
# with DLLs installed in the dll or bin dir. of that toolchain.
#
# 2019-10-02: Updated to work with FrankenVICE (Debian cross-compiler using
#             Fedora packages for Gtk3/GLib)
#             Currently a bit flakey, but it seems to work.


  libm=`$COMPILER -print-file-name=libm.a`
  echo "libm.a = '$libm'"
  location=`dirname $libm`
  loc=`dirname $location`
  echo "loc = $loc"
    if test -d "$loc/dll"
  then dlldir="$loc/dll"
    else dlldir="$loc/bin"
  fi
  dlls=`$OBJDUMP -p src/x64sc.exe | gawk '/^\\tDLL N/{print $3;}'`
  for i in $dlls
  do test -e $dlldir/$i&&cp $dlldir/$i $BUILDPATH
  done
  # A few of these libs cannot be found by frankenvice, so perhaps we need to install
  # these or alter this command:
  cp $dlldir/lib{bz2-1,freetype-6,gcc_s_*,croco-0.6-3,lzma-5,rsvg-2-2,xml2-2}.dll $BUILDPATH
  gccname=`$COMPILER -print-file-name=libgcc.a`
  gccdir=`dirname $gccname`
  dlls=`find $gccdir -name 'libgcc*.dll'`
  test -n "$dlls"&&cp $dlls $BUILDPATH
  get_dll_deps
  get_dll_deps
  current=`pwd`
  cd $loc
  echo cp --parents lib/gdk-pixbuf-2.0/2.*/loaders.cache lib/gdk-pixbuf-2.0/2.*/loaders/libpixbufloader-{png,svg,xpm}.dll $BUILDPATH
  cp --parents lib/gdk-pixbuf-2.0/2.*/loaders.cache lib/gdk-pixbuf-2.0/2.*/loaders/libpixbufloader-{svg,xpm}.dll $BUILDPATH
  test -e lib/gdk-pixbuf-2.0/2.*/loaders/libpixbufloader-png.dll&&cp --parents lib/gdk-pixbuf-2.0/2.*/loaders/libpixbufloader-png.dll $BUILDPATH
  # update loaders.cache
  cat <<EOF > $BUILDPATH/lib/gdk-pixbuf-2.0/2.10.0/loaders.cache
# Generated by src/arc/gtk3/make-bindist_win32.h
# Ugly hack which can break at any moment

"lib\\\\gdk-pixbuf-2.0\\\\2.10.0\\\\loaders\\\\libpixbufloader-svg.dll"
"svg" 6 "gdk-pixbuf" "Scalable Vector Graphics" "LGPL"
"image/svg+xml" "image/svg" "image/svg-xml" "image/vnd.adobe.svg+xml" "text/xml-svg" "image/svg+xml-compressed" ""
"svg" "svgz" "svg.gz" ""
" <svg" "*    " 100
" <!DOCTYPE svg" "*           " 100

# Empty line after even the last entry is required, otherwise the parser fails. A little sucky. 
EOF
  cp --parents -a share/icons/Adwaita/{index.*,16x16,scalable} $BUILDPATH
  rm -r -f $BUILDPATH/share/icons/Adwaita/*/emotes
  # Breaks: no hicolor/ in either Debian or Fedora, but doesn't seem to matter
  cp --parents share/icons/hicolor/index.theme $BUILDPATH
  cp --parents share/glib-2.0/schemas/gschemas.compiled $BUILDPATH
  cp bin/gspawn-win??-helper*.exe $BUILDPATH
  cd $current
fi

cp -a $TOPSRCDIR/data/C128 $TOPSRCDIR/data/C64 $BUILDPATH
cp -a $TOPSRCDIR/data/C64DTV $TOPSRCDIR/data/CBM-II $BUILDPATH
cp -a $TOPSRCDIR/data/DRIVES $TOPSRCDIR/data/PET $BUILDPATH
cp -a $TOPSRCDIR/data/PLUS4 $TOPSRCDIR/data/PRINTER $BUILDPATH
cp -a $TOPSRCDIR/data/SCPU64 $TOPSRCDIR/data/VIC20 $BUILDPATH
rm -f `find $BUILDPATH -name "Makefile*"`
rm -f `find $BUILDPATH -name "sdl_*"`
mkdir $BUILDPATH/gui
cp $TOPBUILDDIR/src/arch/gtk3/data/vice.gresource $BUILDPATH/gui
cp $TOPSRCDIR/data/fonts/CBM.ttf $BUILDPATH/gui
cp -a $TOPSRCDIR/doc/html $BUILDPATH
cp -a -u $TOPBUILDDIR/doc/html $BUILDPATH
rm -f $BUILDPATH/html/Makefile* $BUILDPATH/html/checklinks.sh $BUILDPATH/html/texi2html
rm -f $BUILDPATH/html/robots.txt $BUILDPATH/html/sitemap.xml
rm -f $BUILDPATH/html/COPYING $BUILDPATH/html/NEWS
cp $TOPSRCDIR/COPYING $TOPSRCDIR/FEEDBACK $TOPSRCDIR/NEWS $TOPSRCDIR/README $BUILDPATH
cp $TOPSRCDIR/doc/readmes/Readme-GTK3.txt $BUILDPATH
mkdir $BUILDPATH/doc
test -e $TOPBUILDDIR/doc/vice.pdf&&cp $TOPBUILDDIR/doc/vice.pdf $BUILDPATH/doc


if test x"$ZIPKIND" = "xzip"; then
  rm -f $BUILDPATH.zip
  cd $BUILDPATH/..
  if test x"$ZIP" = "x"
    then zip -r -9 -q $BUILDPATH.zip $GTK3NAME-$VICEVERSION-$WINXX$SVN_SUFFIX
    else $ZIP $BUILDPATH.zip $GTK3NAME-$VICEVERSION-$WINXX$SVN_SUFFIX
  fi
  rm -r -f $BUILDPATH
  echo "$WINXX GTK3 port binary distribution archive generated as:"
  echo "(Bash path): $BUILDPATH.zip"
  test x"$CROSS" != "xtrue"&&echo "(Windows path): '`cygpath -wa \"$BUILDPATH.zip\"`'"
else
  echo "$WINXX GTK3 port binary distribution directory generated as:"
  echo "(Bash path): $BUILDPATH/"
  test x"$CROSS" != "xtrue"&&echo "(Windows path): '`cygpath -wa \"$BUILDPATH/\"`'"
fi

if test x"$ENABLEARCH" = "xyes"; then
  echo ''
  echo 'Warning: The binaries are optimized for your system.'
  echo 'They might not run on a different system.'
  echo 'Configure with --disable-arch to avoid that.'
  echo ''
fi
