#!/usr/bin/python
from bs4 import BeautifulSoup
import urllib3

http = urllib3.PoolManager()

url = '192.168.42.53'
r = http.request('GET', url)
html = r.data

soup = BeautifulSoup(html,'lxml')
readme = soup.find_all('div',id='p')
