import os
import json
import time
from bs4 import BeautifulSoup
from selenium import webdriver
from selenium.webdriver.chrome.service import Service
from webdriver_manager.chrome import ChromeDriverManager
from selenium.webdriver.common.by import By
from selenium.webdriver.support.ui import WebDriverWait
from selenium.webdriver.support import expected_conditions as EC

def parse_table(table_soup):
    rows = table_soup.find_all('tr')
    headers = []
    parsed_data = []
    
    for row in rows:
        cells = row.find_all(['td', 'th'])
        if not cells:
            continue
        
        row_data = [" ".join(cell.get_text(strip=True).split()) for cell in cells]
        
        if len(row_data) <= 1:
            continue
            
        if not headers:
            headers = row_data
            continue
            
        if len(row_data) == len(headers):
            parsed_data.append(dict(zip(headers, row_data)))
            
    return parsed_data

def parse_universal_page(url):
    options = webdriver.ChromeOptions()
    options.add_argument("--headless=new")  
    options.add_argument("--disable-gpu")
    options.add_argument("--no-sandbox")
    options.add_argument("--window-size=1920,1080")

    driver = webdriver.Chrome(service=Service(ChromeDriverManager().install()), options=options)
    master_data = {}
    
    try:
        driver.get(url)
        WebDriverWait(driver, 15).until(EC.presence_of_element_located((By.TAG_NAME, "body")))

        driver.execute_script("""
            var divs = document.querySelectorAll('div[id^="tabl-"]');
            divs.forEach(function(div) { div.style.display = 'block'; });
        """)
        time.sleep(1.5) 

        soup = BeautifulSoup(driver.page_source, "html.parser")
        all_tables = soup.find_all('table')

        for table in all_tables:
            title = "Без названия"
            
            parent_div = table.find_parent('div', id=lambda x: x and x.startswith('tabl-'))
            if parent_div:
                target_id = parent_div.get('id')
                btn = soup.find('p', onclick=lambda x: x and f"'{target_id}'" in x)
                if btn:
                    title = " ".join(btn.get_text(strip=True).split())
            
            if title == "Без названия":
                prev_elements = table.find_all_previous(['p', 'h1', 'h2', 'h3', 'h4'])
                for el in prev_elements:
                    text = " ".join(el.get_text(strip=True).split())
                    if len(text) > 3:
                        title = text
                        break
            
            original_title = title
            counter = 1
            while title in master_data:
                title = f"{original_title} (Таблица {counter})"
                counter += 1

            table_data = parse_table(table)
            if table_data:
                master_data[title] = table_data
                
    except Exception as e:
        print(f"  [Ошибка] {e}")
    finally:
        driver.quit()

    return master_data

# --- Основной блок выполнения ---
if __name__ == "__main__":
    os.makedirs(".\\scrapes", exist_ok=True)
    
    input_file = "tableURLsToSkan.txt"
    
    if not os.path.exists(input_file):
        print(f"Файл {input_file} не найден!")
    else:
        with open(input_file, "r", encoding="utf-8") as file:
            urls_to_parse = [line.strip() for line in file if line.strip()]

        print(f"Загружено {len(urls_to_parse)} ссылок для парсинга.\n")

        # Общий словарь для ВСЕХ страниц
        all_pages_data = {}

        for index, url in enumerate(urls_to_parse, 1):
            print(f"[{index}/{len(urls_to_parse)}] Обработка: {url}")
            
            full_data = parse_universal_page(url)
            
            if full_data:
                # Ключ верхнего уровня — это сам URL
                # убираем домен
                short_key = url.replace("https://synergyuniversity.ru", "")
                if not short_key:
                    short_key = "/"
                    
                all_pages_data[short_key] = full_data
                print(f"   {len(full_data)} таблиц добавлено\n")
            else:
                print(f"   Таблиц не найдено\n")

        #  Сохраняем ВСЁ в один файл
        if all_pages_data:
            filepath = ".\\scrapes\\synergy_all_pages.json"
            with open(filepath, "w", encoding="utf-8") as file:
                json.dump(all_pages_data, file, ensure_ascii=False, indent=4)
            
            total_tables = sum(len(tables) for tables in all_pages_data.values())
            print(f" Готово! Всего {len(all_pages_data)} страниц и {total_tables} таблиц.")
            print(f" Сохранено в: {filepath}")
        else:
            print(" Ничего не собрано.")