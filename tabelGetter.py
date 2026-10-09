import requests
from bs4 import BeautifulSoup


def getTable(url):
    url = url


    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36"
    }

    response = requests.get(url, headers=headers)

    if response.status_code == 200:

        # Парсим HTML при помощи Beautiful Soup
        soup = BeautifulSoup(response.text, 'html.parser')

        # Открываем файл для записи (режим 'w') с поддержкой UTF-8
        with open("pageOutput.html", "w", encoding="utf-8") as f:
            f.write(soup.prettify())

        # CSS-селектор для основных таблиц
        table = soup.find('table', {'class': 'table'})
        try:
            tableHeaders = []
            tableData = []
            maxColumns = 0
            

            #Берём номера колонок потому что вот так в синергии таблицы устроены
            for unit in table.find_all('tr')[1].find_all('td'):
                maxColumns += 1

            #Берём заголовки
            for row in table.find_all('tr')[:1]:
                columns = row.find_all('th')
                for i in range(maxColumns):
                    tableHeaders.append(columns[i].text.strip())

            #Берём данные из таблицы
            for row in table.find_all('tr')[2:]:
                columns = row.find_all('td')
                rowData = []
                if len(columns) > 1:
                    for i in range(maxColumns):
                        rowData.append(columns[i].text.strip())
                else:
                    rowData.append(columns[0].text.strip())
                tableData.append(rowData) 

            return tableHeaders, tableData
        except AttributeError:
            return "На странице не найдено подходящих таблиц"
        except IndexError:
            return "На странице не найдено подходящих таблиц"
# print(getTable('https://synergyuniversity.ru/sveden/common'))