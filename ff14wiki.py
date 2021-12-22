import requests
import urllib3
from bs4 import BeautifulSoup
start_url = 'https://ff14.huijiwiki.com/wiki/%E4%B9%9D%E5%AE%AB%E5%B9%BB%E5%8D%A1%E5%8D%A1%E7%89%8C'

# url='https://mss0.bdstatic.com/se/static/act/captain/bundles/458/a6dc3abe.25ed7fbc.js'
headers = {"User-Agent":
           "Mozilla/5.0 (Windows NT 6.1; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/91.0.4472.124 Safari/537.36"}


def get_source():
    """
    获取网页源代码。
    :param url: 网址
    :return: 网页源代码
    """
    html = requests.get(start_url,headers=headers)
    return html.content.decode('utf-8')  # 这个网页需要使用utf-8方式解码才能让中文正常显示


def get_label():
    html=get_source()
    bsobj = BeautifulSoup(html, 'html.parser')
    # titleList = bsobj.find('table').find_all("tr")
    trList = bsobj.find_all("tr")
    list=[]
    for tr in trList:
        _list=[]
        tdList=tr.find_all("td")
        for i in range(len(tdList)):
            if(not (i==0 or i==2 or i==3 or i==10)):
                if(i==5 and tdList[i].text==''):
                    _list.append('无类型')
                else:
                    _list.append(tdList[i].text)
        list.append(','.join(_list))
        # list.append(_list)
    del list[0]
    return (';'.join(list))
    # return list

if __name__ == "__main__":
    print(get_label())