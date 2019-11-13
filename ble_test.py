#ble_scan_connect.py:
from bluepy.btle import Peripheral, UUID
from bluepy.btle import Scanner, DefaultDelegate
class ScanDelegate(DefaultDelegate):
    def __init__(self):
	DefaultDelegate.__init__(self)
    def handleDiscovery(self, dev, isNewDev, isNewData):
	if isNewDev:
	    print "Discovered device", dev.addr
	elif isNewData:
	    print "Received new data from", dev.addr
scanner = Scanner().withDelegate(ScanDelegate())
devices = scanner.scan(10.0)
n=0
for dev in devices:
    print "%d: Device %s (%s), RSSI=%d dB" % (n, dev.addr, dev.addrType, dev.rssi)
    n += 1
    for (adtype, desc, value) in dev.getScanData():
	print "  %s = %s" % (desc, value)
number = input('Enter your device number: ')
print('Device', number)
print(devices[number].addr)
print "Connecting..."
dev = Peripheral(devices[number].addr, 'public')
print "Services..."
for svc in dev.services:
    print str(svc)
try:
    testService= dev.getServiceByUUID("f0001110-0415-4000-B000-000000000000")
    for ch in testService.getCharacteristics():
	print str(ch)
    ch= dev.getCharacteristics(uuid="f0001111-0415-4000-B000-000000000000")[0]
    if (ch.supportsRead()):
	print ch.read()
finally:
    dev.disconnect()
