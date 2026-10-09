import requests
from bs4 import BeautifulSoup
import json
import os


def getTable(url):
    
    url = url.strip()

    headers = {
        "User-Agent": "Mozilla/5.0 (Windows NT 10.0; Win64; x64) AppleWebKit/537.36 (KHTML, like Gecko) Chrome/58.0.3029.110 Safari/537.36"
    }

    try:
        response = requests.get(url, headers=headers)
        if response.status_code != 200:
            return {"status": f"Ошибка запроса: код {response.status_code}"}
    except Exception as e:
        return {"status": f"Не удалось подключиться к сайту: {e}"}

    soup = BeautifulSoup(response.text, 'html.parser')

    tables = soup.find_all('table', {'class': 'table'})
    
    if not tables:
        return {"status": "На странице не найдено подходящих таблиц"}

    allTablesData = []

    for index, table in enumerate(tables, start=1):
        try:
            tableHeaders = []
            tableData = []
            
            all_rows = table.find_all('tr')
            if not all_rows:
                continue

            first_data_row = next((r for r in all_rows if r.find_all('td')), None)
            if not first_data_row:
                continue
            maxColumns = len(first_data_row.find_all('td'))

            for row in all_rows[:1]:
                columns = row.find_all('th')
                for i in range(min(maxColumns, len(columns))):
                    tableHeaders.append(columns[i].text.strip())

            for row in all_rows[1:]:
                columns = row.find_all('td')
                if not columns:
                    continue
                    
                rowData = []
                for i in range(min(maxColumns, len(columns))):
                    cell = columns[i]
                    
                    # Проверяем, есть ли ссылка <a> внутри ячейки
                    link = cell.find('a')
                    if link and link.get('href'):
                        link_text = link.text.strip()
                        href = link.get('href')
                        
                        if href.startswith('/'):
                            href = "https://synergyuniversity.ru" + href
                            
                        cell_value = f"{link_text} ({href})"
                    else:
                        cell_value = cell.text.strip()
                        
                    rowData.append(cell_value)
                
                if rowData:
                    tableData.append(rowData) 

            allTablesData.append({
                "table_number": index,
                "headers": tableHeaders,
                "rows": tableData
            })

        except Exception as e:
            print(f"Ошибка при обработке таблицы {index} на {url}: {e}")
            continue

    return {
        "url": url,
        "tables_count": len(allTablesData),
        "tables": allTablesData
    }


# --- Основной блок выполнения ---
os.makedirs(".\\scrapes", exist_ok=True)

with open("tableURLsToSkan.txt", "r", encoding="utf-8") as file:
    urlList = [line.strip() for line in file if line.strip()]

for url in urlList:
    print(f"Parsing: {url}")
    dataToSave = getTable(url)
    safeName = url.replace("https://", "").replace("/", "_").replace(":", "")
    with open(f".\\scrapes\\{safeName}.json", "w", encoding="utf-8") as file:
        json.dump(dataToSave, file, ensure_ascii=False, indent=4)

print("Парсинг успешно завершен!")
