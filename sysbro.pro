TEMPLATE = subdirs

SUBDIRS += \
           src \
           sysbro-delete-files \
           sysbro-startup-apps \
           sysbro-network-test \
           sysbro-express \
           sysbro-boot-assistant \
           sysbro-file-shredder

# Automating generation .qm files from .ts files
!system($$PWD/translate_generation.sh): error("Failed to generate translation")
