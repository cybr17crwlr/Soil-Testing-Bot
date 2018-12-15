from bs4 import BeautifulSoup as bs
import urllib3
import time

http = urllib3.PoolManager()
url = '192.168.43.52'

while True:
    r = http.request('GET', url)
    html = r.data
    soup = bs(html, 'lxml')
    data = soup.find_all('p')
    print(data)
    state = data[0].text[17:]
    N = int(data[1].text[4:])
    P = int(data[2].text[4:])
    K = int(data[3].text[4:])
    print(state)
    if state == 'Analysing':
        print(N)
        print(P)
        print(K)
    time.sleep(2)
    
