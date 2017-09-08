''' THE MAIN PYTHON CODE TO DRIVE THE RASPBERRY PI- IBM BLUEMIX DUO'''
#importing necessary modules
import json
import sys
from os.path import join,dirname
from os import environ
from watson_developer_cloud import VisualRecognitionV3 as vr
from pprint import pprint

#instantiating
visual_recognition = vr(vr.latest_version, api_key='0234986d7c042310503a1e2477f1f8579a190040')
with open('C:\Users\Pritesh J Shah\Desktop\VisualRecognition\leaf_negative_examples\leaf69.jpg', 'rb') as image_file:
    a=json.dumps(visual_recognition.classify(images_file=image_file, threshold=0, classifier_ids=['PestControl_834594187']), indent=2)#retrieving the JSON object
    js=json.loads(a)#parsing
    a=js['images'][0]['classifiers'][0]['classes'][0]['score']#parsing
    b=js['images'][0]['classifiers'][0]['classes'][1]['score']#parsing
    if(a>b):
        print(js['images'][0]['classifiers'][0]['classes'][0]['class'])
    else:                                                                   #checking for pest/not pest 
        print(js['images'][0]['classifiers'][0]['classes'][1]['class'])
#at this point we get whether the image contains pests or not.

