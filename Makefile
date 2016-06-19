all:
	make -C ./common/
	make -C ./common/tests/
	make -C ./net/


clean:
	make -C ./common/ clean
	make -C ./common/tests clean
	make -C ./net/ clean

.PHONY: all clean
