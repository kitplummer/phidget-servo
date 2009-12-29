DESCRIPTION = "phidget-servo driver command"

PR = "r0"

DEPENDS = "phidgets-oe"

SRC_URI = " \
  file://phidget-servo.c \
  file://phidget21.h \
  file://Makefile \
 "

S = "${WORKDIR}"

do_install () {
    install -d ${D}${bindir}/
    install -m 0755 ${S}/phidget-servo ${D}${bindir}/
}

FILES_${PN} = "${bindir}/phidget-servo"

