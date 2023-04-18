import numpy as np
import argparse
from PIL import Image

parser = argparse.ArgumentParser(
                    prog='ImageTransform',
                    description='I make a tool to help us transform a colorful image to a const C array',
                    epilog='Text at the bottom of help')

parser.add_argument('filename')           # positional argument
parser.add_argument('-o', '--out_path',default='./out.c')      # option that takes a value

args=parser.parse_args()


def parse_image(img):
    img=np.asarray(img)
    w,h=img.shape[0],img.shape[1]
    img=np.reshape(img,(-1,3))
    def cal(vec):
        v=vec[0]*16**4+vec[1]*16**2+vec[2]
        return hex(v)
    
    array=[]
    for vec in img:
        array.append(cal(vec))
    
    
    return "const uint32_t image[]={"+','.join(array)+'};\r\n'\
        +f'int image_w={w};'+f"int image_h={h};"


image=Image.open(args.filename)
image=image.convert("RGB")

with open(args.out_path,'w') as f:
    f.write(parse_image(image))

















