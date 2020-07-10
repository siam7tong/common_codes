import xml.etree.ElementTree as ET
import glob
import shutil
import os

src = "src/"
dst = "dst/"
xmls = glob.glob(src+"*.xml")
num = 0
for xml in xmls:
    
    tree = ET.parse(xml)  # <class 'xml.etree.ElementTree.ElementTree'>
    root = tree.getroot()           # 获取根节点 <Element 'data' at 0x02BF6A80>
    if len(root.findall("object")) >2:
        continue
    if len(root.findall("object")) == 1:
        num +=1
    hasGun = False
    for obj in root.iter("object"):
        name = obj.find("name")
        if name.text=="gun":
            hasGun = True
    if hasGun:
        jpg = xml[:-4]+".jpg"
        xmlbase = os.path.basename(xml)
        jpgbase = xmlbase[:-4]+".jpg"
        
        #shutil.copy(xml, dst+xmlbase)
        #shutil.copy(jpg, dst+jpgbase)
print(num)
