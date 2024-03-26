
from selenium import webdriver
from webdriver_manager.chrome import ChromeDriverManager, ChromeDriver
import time

# deschidere browser
# browser = webdriver.Chrome(ChromeDriverManager(version="121.0.6167.140").install())
chrome_driver_path = r'C:\Users\gabig\Downloads\chrome-win64\chrome.exe'
browser = webdriver.Chrome()
browser.get("https://academicinfo.ubbcluj.ro/")
browser.maximize_window()

time.sleep(5)

# introducere date
browser.find_element('name', 'txtUsername').send_keys('username-ul tau')
browser.find_element('name', 'txtPassword').send_keys('parola ta')

# sleep
import time
# time.sleep(10)
#
# # nu sunt robot
# import mouse
# mouse.move("500", "440")
# mouse.click(button='left')

time.sleep(60)

# apasare log in
browser.find_element('name', 'btnLogin').click()

# intrare la note provizorii
browser.find_element('class name', 'a2').click()
browser.find_element('id', 'ctl00_hlNote_').click()

# verificare daca s-au pus

g = 0
while g == 0:
    browser.refresh()
    time.sleep(10)
    text = browser.find_element('class name', 'table.table-hover.table-striped.w-auto.table-bordered').text
    if "Baze de date  " in text:
        pass
    else:
        gasit = webdriver.Chrome(ChromeDriverManager().install())
        gasit.get("https://academicinfo.ubbcluj.ro/")
        gasit.maximize_window()
        break

    if "Probabilităţi şi statistică  " in text:
        pass
    else:
        gasit = webdriver.Chrome()
        gasit.get("https://academicinfo.ubbcluj.ro/")
        gasit.maximize_window()
        break




