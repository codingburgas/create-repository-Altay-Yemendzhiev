#include "../include/presentation.h"

#include "../include/logic.h"

#include <QApplication>
#include <QComboBox>
#include <QDoubleSpinBox>
#include <QFrame>
#include <QFont>
#include <QGridLayout>
#include <QGroupBox>
#include <QHeaderView>
#include <QIntValidator>
#include <QItemSelectionModel>
#include <QLabel>
#include <QLineEdit>
#include <QList>
#include <QMainWindow>
#include <QMessageBox>
#include <QModelIndex>
#include <QPushButton>
#include <QSignalBlocker>
#include <QVector>
#include <QSpinBox>
#include <QStackedWidget>
#include <QTableWidget>
#include <QTableWidgetItem>
#include <QVBoxLayout>

#include <cstring>
#include <algorithm>
#include <functional>

struct languageText
{
    QString languageName;
    QString windowTitle;
    QString products;
    QString settings;
    QString addProduct;
    QString editProduct;
    QString sortProducts;
    QString file;
    QString productName;
    QString price;
    QString quantity;
    QString add;
    QString updateQuantity;
    QString deleteProduct;
    QString searchName;
    QString exactQuantity;
    QString clearFilters;
    QString sortField;
    QString sortAlgorithm;
    QString sortByPrice;
    QString sortByQuantity;
    QString quickSort;
    QString bogoSort;
    QString applySort;
    QString totalValue;
    QString save;
    QString reload;
    QString theme;
    QString language;
    QString selectedProduct;
    QString noSelection;
    QString ready;
    QString invalidInput;
    QString productAdded;
    QString quantityUpdated;
    QString productDeleted;
    QString sorted;
    QString bogoBlocked;
    QString saved;
    QString loaded;
    QString noProducts;
    QString confirmDeleteTitle;
    QString confirmDeleteText;
};

struct themeDefinition
{
    QString name;
    QString window;
    QString surface;
    QString surfaceAlt;
    QString border;
    QString text;
    QString mutedText;
    QString accent;
    QString accentSoft;
    QString button;
    QString buttonHover;
    QString danger;
    QString tableHeader;
};

static QVector<languageText> createTexts()
{
    return {
        {
            QStringLiteral("English"),
            QStringLiteral("Lapis Technologies"),
            QStringLiteral("Products"),
            QStringLiteral("Settings"),
            QStringLiteral("Add product"),
            QStringLiteral("Edit product"),
            QStringLiteral("Sort"),
            QStringLiteral("File"),
            QStringLiteral("Product name"),
            QStringLiteral("Price"),
            QStringLiteral("Quantity"),
            QStringLiteral("Add"),
            QStringLiteral("Update quantity"),
            QStringLiteral("Delete product"),
            QStringLiteral("Search by name"),
            QStringLiteral("Exact quantity"),
            QStringLiteral("Clear filters"),
            QStringLiteral("Sort field"),
            QStringLiteral("Algorithm"),
            QStringLiteral("Price"),
            QStringLiteral("Quantity"),
            QStringLiteral("Quick Sort"),
            QStringLiteral("Bogo Sort"),
            QStringLiteral("Apply sort"),
            QStringLiteral("Total value"),
            QStringLiteral("Save"),
            QStringLiteral("Reload"),
            QStringLiteral("Theme"),
            QStringLiteral("Language"),
            QStringLiteral("Selected product"),
            QStringLiteral("Select a product from the table."),
            QStringLiteral("Ready."),
            QStringLiteral("Invalid product data."),
            QStringLiteral("Product added."),
            QStringLiteral("Quantity updated."),
            QStringLiteral("Product deleted."),
            QStringLiteral("Products sorted."),
            QStringLiteral("Bogo Sort is blocked for more than 8 products."),
            QStringLiteral("Data saved."),
            QStringLiteral("Data loaded."),
            QStringLiteral("No products match the current filters."),
            QStringLiteral("Delete product"),
            QStringLiteral("Delete the selected product?")
        },
        {
            QStringLiteral("Български"),
            QStringLiteral("Lapis Technologies"),
            QStringLiteral("Продукти"),
            QStringLiteral("Настройки"),
            QStringLiteral("Добави продукт"),
            QStringLiteral("Редактирай"),
            QStringLiteral("Сортиране"),
            QStringLiteral("Файл"),
            QStringLiteral("Име на продукт"),
            QStringLiteral("Цена"),
            QStringLiteral("Количество"),
            QStringLiteral("Добави"),
            QStringLiteral("Обнови количество"),
            QStringLiteral("Изтрий продукт"),
            QStringLiteral("Търсене по име"),
            QStringLiteral("Точно количество"),
            QStringLiteral("Изчисти филтрите"),
            QStringLiteral("Поле за сортиране"),
            QStringLiteral("Алгоритъм"),
            QStringLiteral("Цена"),
            QStringLiteral("Количество"),
            QStringLiteral("Quick Sort"),
            QStringLiteral("Bogo Sort"),
            QStringLiteral("Сортирай"),
            QStringLiteral("Обща стойност"),
            QStringLiteral("Запази"),
            QStringLiteral("Презареди"),
            QStringLiteral("Тема"),
            QStringLiteral("Език"),
            QStringLiteral("Избран продукт"),
            QStringLiteral("Изберете продукт от таблицата."),
            QStringLiteral("Готово."),
            QStringLiteral("Невалидни данни."),
            QStringLiteral("Продуктът е добавен."),
            QStringLiteral("Количеството е обновено."),
            QStringLiteral("Продуктът е изтрит."),
            QStringLiteral("Продуктите са сортирани."),
            QStringLiteral("Bogo Sort е блокиран за повече от 8 продукта."),
            QStringLiteral("Данните са запазени."),
            QStringLiteral("Данните са заредени."),
            QStringLiteral("Няма продукти с тези филтри."),
            QStringLiteral("Изтриване"),
            QStringLiteral("Да се изтрие ли избраният продукт?")
        },
        {
            QStringLiteral("Español"),
            QStringLiteral("Lapis Technologies"),
            QStringLiteral("Productos"),
            QStringLiteral("Ajustes"),
            QStringLiteral("Añadir producto"),
            QStringLiteral("Editar producto"),
            QStringLiteral("Ordenar"),
            QStringLiteral("Archivo"),
            QStringLiteral("Nombre del producto"),
            QStringLiteral("Precio"),
            QStringLiteral("Cantidad"),
            QStringLiteral("Añadir"),
            QStringLiteral("Actualizar cantidad"),
            QStringLiteral("Eliminar producto"),
            QStringLiteral("Buscar por nombre"),
            QStringLiteral("Cantidad exacta"),
            QStringLiteral("Limpiar filtros"),
            QStringLiteral("Campo"),
            QStringLiteral("Algoritmo"),
            QStringLiteral("Precio"),
            QStringLiteral("Cantidad"),
            QStringLiteral("Quick Sort"),
            QStringLiteral("Bogo Sort"),
            QStringLiteral("Ordenar"),
            QStringLiteral("Valor total"),
            QStringLiteral("Guardar"),
            QStringLiteral("Recargar"),
            QStringLiteral("Tema"),
            QStringLiteral("Idioma"),
            QStringLiteral("Producto seleccionado"),
            QStringLiteral("Selecciona un producto de la tabla."),
            QStringLiteral("Listo."),
            QStringLiteral("Datos no válidos."),
            QStringLiteral("Producto añadido."),
            QStringLiteral("Cantidad actualizada."),
            QStringLiteral("Producto eliminado."),
            QStringLiteral("Productos ordenados."),
            QStringLiteral("Bogo Sort está bloqueado para más de 8 productos."),
            QStringLiteral("Datos guardados."),
            QStringLiteral("Datos cargados."),
            QStringLiteral("No hay productos con estos filtros."),
            QStringLiteral("Eliminar producto"),
            QStringLiteral("¿Eliminar el producto seleccionado?")
        },
        {
            QStringLiteral("Français"),
            QStringLiteral("Lapis Technologies"),
            QStringLiteral("Produits"),
            QStringLiteral("Paramètres"),
            QStringLiteral("Ajouter un produit"),
            QStringLiteral("Modifier"),
            QStringLiteral("Trier"),
            QStringLiteral("Fichier"),
            QStringLiteral("Nom du produit"),
            QStringLiteral("Prix"),
            QStringLiteral("Quantité"),
            QStringLiteral("Ajouter"),
            QStringLiteral("Mettre à jour"),
            QStringLiteral("Supprimer"),
            QStringLiteral("Recherche par nom"),
            QStringLiteral("Quantité exacte"),
            QStringLiteral("Effacer les filtres"),
            QStringLiteral("Champ"),
            QStringLiteral("Algorithme"),
            QStringLiteral("Prix"),
            QStringLiteral("Quantité"),
            QStringLiteral("Quick Sort"),
            QStringLiteral("Bogo Sort"),
            QStringLiteral("Trier"),
            QStringLiteral("Valeur totale"),
            QStringLiteral("Enregistrer"),
            QStringLiteral("Recharger"),
            QStringLiteral("Thème"),
            QStringLiteral("Langue"),
            QStringLiteral("Produit sélectionné"),
            QStringLiteral("Sélectionnez un produit dans le tableau."),
            QStringLiteral("Prêt."),
            QStringLiteral("Données invalides."),
            QStringLiteral("Produit ajouté."),
            QStringLiteral("Quantité mise à jour."),
            QStringLiteral("Produit supprimé."),
            QStringLiteral("Produits triés."),
            QStringLiteral("Bogo Sort est bloqué pour plus de 8 produits."),
            QStringLiteral("Données enregistrées."),
            QStringLiteral("Données chargées."),
            QStringLiteral("Aucun produit avec ces filtres."),
            QStringLiteral("Supprimer"),
            QStringLiteral("Supprimer le produit sélectionné ?")
        },
        {
            QStringLiteral("Deutsch"),
            QStringLiteral("Lapis Technologies"),
            QStringLiteral("Produkte"),
            QStringLiteral("Einstellungen"),
            QStringLiteral("Produkt hinzufügen"),
            QStringLiteral("Produkt bearbeiten"),
            QStringLiteral("Sortieren"),
            QStringLiteral("Datei"),
            QStringLiteral("Produktname"),
            QStringLiteral("Preis"),
            QStringLiteral("Menge"),
            QStringLiteral("Hinzufügen"),
            QStringLiteral("Menge aktualisieren"),
            QStringLiteral("Produkt löschen"),
            QStringLiteral("Nach Name suchen"),
            QStringLiteral("Genaue Menge"),
            QStringLiteral("Filter löschen"),
            QStringLiteral("Feld"),
            QStringLiteral("Algorithmus"),
            QStringLiteral("Preis"),
            QStringLiteral("Menge"),
            QStringLiteral("Quick Sort"),
            QStringLiteral("Bogo Sort"),
            QStringLiteral("Sortieren"),
            QStringLiteral("Gesamtwert"),
            QStringLiteral("Speichern"),
            QStringLiteral("Neu laden"),
            QStringLiteral("Design"),
            QStringLiteral("Sprache"),
            QStringLiteral("Ausgewähltes Produkt"),
            QStringLiteral("Wählen Sie ein Produkt aus der Tabelle."),
            QStringLiteral("Bereit."),
            QStringLiteral("Ungültige Daten."),
            QStringLiteral("Produkt hinzugefügt."),
            QStringLiteral("Menge aktualisiert."),
            QStringLiteral("Produkt gelöscht."),
            QStringLiteral("Produkte sortiert."),
            QStringLiteral("Bogo Sort ist bei mehr als 8 Produkten blockiert."),
            QStringLiteral("Daten gespeichert."),
            QStringLiteral("Daten geladen."),
            QStringLiteral("Keine Produkte mit diesen Filtern."),
            QStringLiteral("Produkt löschen"),
            QStringLiteral("Ausgewähltes Produkt löschen?")
        },
        {
            QStringLiteral("Türkçe"),
            QStringLiteral("Lapis Technologies"),
            QStringLiteral("Ürünler"),
            QStringLiteral("Ayarlar"),
            QStringLiteral("Ürün ekle"),
            QStringLiteral("Ürünü düzenle"),
            QStringLiteral("Sırala"),
            QStringLiteral("Dosya"),
            QStringLiteral("Ürün adı"),
            QStringLiteral("Fiyat"),
            QStringLiteral("Adet"),
            QStringLiteral("Ekle"),
            QStringLiteral("Adedi güncelle"),
            QStringLiteral("Ürünü sil"),
            QStringLiteral("Ada göre ara"),
            QStringLiteral("Tam adet"),
            QStringLiteral("Filtreleri temizle"),
            QStringLiteral("Sıralama alanı"),
            QStringLiteral("Algoritma"),
            QStringLiteral("Fiyat"),
            QStringLiteral("Adet"),
            QStringLiteral("Quick Sort"),
            QStringLiteral("Bogo Sort"),
            QStringLiteral("Sırala"),
            QStringLiteral("Toplam değer"),
            QStringLiteral("Kaydet"),
            QStringLiteral("Yeniden yükle"),
            QStringLiteral("Tema"),
            QStringLiteral("Dil"),
            QStringLiteral("Seçili ürün"),
            QStringLiteral("Tablodan bir ürün seçin."),
            QStringLiteral("Hazır."),
            QStringLiteral("Geçersiz veri."),
            QStringLiteral("Ürün eklendi."),
            QStringLiteral("Adet güncellendi."),
            QStringLiteral("Ürün silindi."),
            QStringLiteral("Ürünler sıralandı."),
            QStringLiteral("Bogo Sort 8 üründen fazlası için engellendi."),
            QStringLiteral("Veriler kaydedildi."),
            QStringLiteral("Veriler yüklendi."),
            QStringLiteral("Bu filtrelerle ürün yok."),
            QStringLiteral("Ürünü sil"),
            QStringLiteral("Seçili ürün silinsin mi?")
        },
        {
            QStringLiteral("Русский"),
            QStringLiteral("Lapis Technologies"),
            QStringLiteral("Товары"),
            QStringLiteral("Настройки"),
            QStringLiteral("Добавить товар"),
            QStringLiteral("Изменить товар"),
            QStringLiteral("Сортировка"),
            QStringLiteral("Файл"),
            QStringLiteral("Название товара"),
            QStringLiteral("Цена"),
            QStringLiteral("Количество"),
            QStringLiteral("Добавить"),
            QStringLiteral("Обновить количество"),
            QStringLiteral("Удалить товар"),
            QStringLiteral("Поиск по названию"),
            QStringLiteral("Точное количество"),
            QStringLiteral("Очистить фильтры"),
            QStringLiteral("Поле"),
            QStringLiteral("Алгоритм"),
            QStringLiteral("Цена"),
            QStringLiteral("Количество"),
            QStringLiteral("Quick Sort"),
            QStringLiteral("Bogo Sort"),
            QStringLiteral("Сортировать"),
            QStringLiteral("Общая стоимость"),
            QStringLiteral("Сохранить"),
            QStringLiteral("Перезагрузить"),
            QStringLiteral("Тема"),
            QStringLiteral("Язык"),
            QStringLiteral("Выбранный товар"),
            QStringLiteral("Выберите товар в таблице."),
            QStringLiteral("Готово."),
            QStringLiteral("Некорректные данные."),
            QStringLiteral("Товар добавлен."),
            QStringLiteral("Количество обновлено."),
            QStringLiteral("Товар удален."),
            QStringLiteral("Товары отсортированы."),
            QStringLiteral("Bogo Sort заблокирован для более чем 8 товаров."),
            QStringLiteral("Данные сохранены."),
            QStringLiteral("Данные загружены."),
            QStringLiteral("Нет товаров с этими фильтрами."),
            QStringLiteral("Удалить товар"),
            QStringLiteral("Удалить выбранный товар?")
        },
        {
            QStringLiteral("עברית"),
            QStringLiteral("Lapis Technologies"),
            QStringLiteral("מוצרים"),
            QStringLiteral("הגדרות"),
            QStringLiteral("הוספת מוצר"),
            QStringLiteral("עריכת מוצר"),
            QStringLiteral("מיון"),
            QStringLiteral("קובץ"),
            QStringLiteral("שם מוצר"),
            QStringLiteral("מחיר"),
            QStringLiteral("כמות"),
            QStringLiteral("הוסף"),
            QStringLiteral("עדכן כמות"),
            QStringLiteral("מחק מוצר"),
            QStringLiteral("חיפוש לפי שם"),
            QStringLiteral("כמות מדויקת"),
            QStringLiteral("נקה מסננים"),
            QStringLiteral("שדה מיון"),
            QStringLiteral("אלגוריתם"),
            QStringLiteral("מחיר"),
            QStringLiteral("כמות"),
            QStringLiteral("Quick Sort"),
            QStringLiteral("Bogo Sort"),
            QStringLiteral("מיין"),
            QStringLiteral("ערך כולל"),
            QStringLiteral("שמור"),
            QStringLiteral("טען מחדש"),
            QStringLiteral("ערכת נושא"),
            QStringLiteral("שפה"),
            QStringLiteral("מוצר נבחר"),
            QStringLiteral("בחר מוצר מהטבלה."),
            QStringLiteral("מוכן."),
            QStringLiteral("נתונים לא תקינים."),
            QStringLiteral("המוצר נוסף."),
            QStringLiteral("הכמות עודכנה."),
            QStringLiteral("המוצר נמחק."),
            QStringLiteral("המוצרים מוינו."),
            QStringLiteral("Bogo Sort חסום עבור יותר מ-8 מוצרים."),
            QStringLiteral("הנתונים נשמרו."),
            QStringLiteral("הנתונים נטענו."),
            QStringLiteral("אין מוצרים עם המסננים האלה."),
            QStringLiteral("מחק מוצר"),
            QStringLiteral("למחוק את המוצר שנבחר?")
        }
    };
}

static QVector<themeDefinition> createThemes()
{
    return {
        {
            QStringLiteral("Slate"),
            QStringLiteral("#f5f7fb"),
            QStringLiteral("#ffffff"),
            QStringLiteral("#eef4f9"),
            QStringLiteral("#d7e2ea"),
            QStringLiteral("#1e1b18"),
            QStringLiteral("#5e6874"),
            QStringLiteral("#2f6f9f"),
            QStringLiteral("#e4f0f8"),
            QStringLiteral("#f8fbfd"),
            QStringLiteral("#eaf3f8"),
            QStringLiteral("#c44a66"),
            QStringLiteral("#e8f1f7")
        },
        {
            QStringLiteral("Cloud"),
            QStringLiteral("#fffaff"),
            QStringLiteral("#ffffff"),
            QStringLiteral("#f2f5f8"),
            QStringLiteral("#dde5ec"),
            QStringLiteral("#1e1b18"),
            QStringLiteral("#68727d"),
            QStringLiteral("#3e92cc"),
            QStringLiteral("#e9f4fb"),
            QStringLiteral("#ffffff"),
            QStringLiteral("#edf6fc"),
            QStringLiteral("#d8315b"),
            QStringLiteral("#edf3f8")
        },
        {
            QStringLiteral("Harbor"),
            QStringLiteral("#eef6fb"),
            QStringLiteral("#fbfdff"),
            QStringLiteral("#e1eef6"),
            QStringLiteral("#c9dce9"),
            QStringLiteral("#182236"),
            QStringLiteral("#586778"),
            QStringLiteral("#0a5f92"),
            QStringLiteral("#dbeef8"),
            QStringLiteral("#f7fbfe"),
            QStringLiteral("#e0eff7"),
            QStringLiteral("#be3d5d"),
            QStringLiteral("#d9eaf4")
        },
        {
            QStringLiteral("Cherry"),
            QStringLiteral("#f7f2f5"),
            QStringLiteral("#ffffff"),
            QStringLiteral("#f3e8ed"),
            QStringLiteral("#e5d3db"),
            QStringLiteral("#241d20"),
            QStringLiteral("#6e6067"),
            QStringLiteral("#b93657"),
            QStringLiteral("#f7dfe7"),
            QStringLiteral("#fffafb"),
            QStringLiteral("#f7e6ec"),
            QStringLiteral("#d8315b"),
            QStringLiteral("#f2dce4")
        },
        {
            QStringLiteral("Midnight"),
            QStringLiteral("#171b22"),
            QStringLiteral("#202731"),
            QStringLiteral("#27313d"),
            QStringLiteral("#3a4858"),
            QStringLiteral("#f4f0f4"),
            QStringLiteral("#b4bdc8"),
            QStringLiteral("#6faed4"),
            QStringLiteral("#24384a"),
            QStringLiteral("#27313d"),
            QStringLiteral("#314053"),
            QStringLiteral("#d45a76"),
            QStringLiteral("#2d3a49")
        }
    };
}

static QString createStyleSheet(const themeDefinition& theme)
{
    return QStringLiteral(
        "QMainWindow, QWidget {"
        "    background: %1;"
        "    color: %5;"
        "    font-family: 'Segoe UI';"
        "    font-size: 10pt;"
        "}"
        "QFrame#topBar, QFrame#actionPanel, QFrame#detailsCard {"
        "    background: %2;"
        "    border: 1px solid %4;"
        "    border-radius: 10px;"
        "}"
        "QFrame#logo {"
        "    background: %7;"
        "    border-radius: 10px;"
        "}"
        "QLabel#logoText {"
        "    background: transparent;"
        "    color: white;"
        "    font-weight: 700;"
        "    font-size: 15pt;"
        "}"
        "QLabel#appTitle {"
        "    background: transparent;"
        "    font-size: 18pt;"
        "    font-weight: 700;"
        "}"
        "QLabel#muted, QLabel#statusLabel {"
        "    background: transparent;"
        "    color: %6;"
        "}"
        "QPushButton {"
        "    background: %9;"
        "    border: 1px solid %4;"
        "    border-radius: 8px;"
        "    padding: 8px 13px;"
        "}"
        "QPushButton:hover {"
        "    background: %10;"
        "}"
        "QPushButton:pressed, QPushButton:checked {"
        "    background: %8;"
        "    border-color: %7;"
        "}"
        "QPushButton#primaryButton {"
        "    background: %7;"
        "    border-color: %7;"
        "    color: white;"
        "    font-weight: 600;"
        "}"
        "QPushButton#dangerButton {"
        "    color: %11;"
        "}"
        "QLineEdit, QSpinBox, QDoubleSpinBox, QComboBox {"
        "    background: %2;"
        "    border: 1px solid %4;"
        "    border-radius: 8px;"
        "    min-height: 22px;"
        "    padding: 7px 10px;"
        "}"
        "QSpinBox, QDoubleSpinBox {"
        "    padding-right: 34px;"
        "}"
        "QSpinBox::up-button, QDoubleSpinBox::up-button {"
        "    subcontrol-origin: border;"
        "    subcontrol-position: top right;"
        "    width: 28px;"
        "    border-left: 1px solid %4;"
        "    border-bottom: 1px solid %4;"
        "    border-top-right-radius: 8px;"
        "    background: %3;"
        "}"
        "QSpinBox::down-button, QDoubleSpinBox::down-button {"
        "    subcontrol-origin: border;"
        "    subcontrol-position: bottom right;"
        "    width: 28px;"
        "    border-left: 1px solid %4;"
        "    border-bottom-right-radius: 8px;"
        "    background: %3;"
        "}"
        "QSpinBox::up-button:hover, QDoubleSpinBox::up-button:hover,"
        "QSpinBox::down-button:hover, QDoubleSpinBox::down-button:hover {"
        "    background: %10;"
        "}"
        "QSpinBox::up-arrow, QDoubleSpinBox::up-arrow {"
        "    image: url(resources/icons/spin-up.svg);"
        "    width: 12px;"
        "    height: 12px;"
        "}"
        "QSpinBox::down-arrow, QDoubleSpinBox::down-arrow {"
        "    image: url(resources/icons/spin-down.svg);"
        "    width: 12px;"
        "    height: 12px;"
        "}"
        "QTableWidget {"
        "    background: %2;"
        "    alternate-background-color: %3;"
        "    border: 1px solid %4;"
        "    border-radius: 10px;"
        "    gridline-color: %4;"
        "    selection-background-color: %8;"
        "    selection-color: %5;"
        "}"
        "QHeaderView::section {"
        "    background: %12;"
        "    border: 0;"
        "    border-right: 1px solid %4;"
        "    border-bottom: 1px solid %4;"
        "    padding: 9px 10px;"
        "    font-weight: 650;"
        "}"
        "QTableCornerButton::section {"
        "    background: %12;"
        "    border: 0;"
        "}"
        "QGroupBox {"
        "    border: 1px solid %4;"
        "    border-radius: 10px;"
        "    margin-top: 12px;"
        "    padding: 16px 12px 12px 12px;"
        "    background: %2;"
        "}"
        "QGroupBox::title {"
        "    subcontrol-origin: margin;"
        "    left: 10px;"
        "    padding: 0 6px;"
        "    color: %6;"
        "}"
    ).arg(
        theme.window,
        theme.surface,
        theme.surfaceAlt,
        theme.border,
        theme.text,
        theme.mutedText,
        theme.accent,
        theme.accentSoft,
        theme.button,
        theme.buttonHover,
        theme.danger,
        theme.tableHeader
    );
}

static QString formatMoney(float value)
{
    return QString::number(value, 'f', 2);
}

static QString productDisplayName(const product& item)
{
    return QString::fromUtf8(item.name);
}

static void copyToProductName(product* item, const QString& name)
{
    const QByteArray bytes = name.trimmed().toUtf8();
    std::strncpy(item->name, bytes.constData(), maxNameLength - 1);
    item->name[maxNameLength - 1] = '\0';
}

/*
 * Purpose: Renders and runs the complete Qt inventory interface.
 * Parameters: inventoryFilePath - CSV path used by load and save actions.
 * Return value: None.
 */
void renderUI(const char* inventoryFilePath)
{
    int argumentCount = 1;
    char appName[] = "InventoryManager";
    char* arguments[] = { appName, nullptr };

    QApplication app(argumentCount, arguments);
    app.setFont(QFont(QStringLiteral("Segoe UI"), 10));

    QVector<languageText> texts = createTexts();
    QVector<themeDefinition> themes = createThemes();

    int currentLanguage = 0;
    int currentTheme = 0;
    int selectedIndex = -1;
    QVector<int> selectedIndexes;

    QMainWindow window;
    window.setMinimumSize(1120, 720);
    window.resize(1280, 760);
    window.setWindowTitle(QStringLiteral("Lapis Technologies"));

    QWidget* rootWidget = new QWidget(&window);
    QVBoxLayout* rootLayout = new QVBoxLayout(rootWidget);
    rootLayout->setContentsMargins(18, 18, 18, 18);
    rootLayout->setSpacing(14);

    QFrame* topBar = new QFrame(rootWidget);
    topBar->setObjectName(QStringLiteral("topBar"));
    QGridLayout* topLayout = new QGridLayout(topBar);
    topLayout->setContentsMargins(16, 14, 16, 14);
    topLayout->setHorizontalSpacing(14);

    QFrame* logoFrame = new QFrame(topBar);
    logoFrame->setObjectName(QStringLiteral("logo"));
    logoFrame->setFixedSize(48, 48);
    QVBoxLayout* logoLayout = new QVBoxLayout(logoFrame);
    logoLayout->setContentsMargins(0, 0, 0, 0);
    QLabel* logoLabel = new QLabel(QStringLiteral("LT"), logoFrame);
    logoLabel->setObjectName(QStringLiteral("logoText"));
    logoLabel->setAlignment(Qt::AlignCenter);
    logoLayout->addWidget(logoLabel);

    QLabel* titleLabel = new QLabel(QStringLiteral("Lapis Technologies"), topBar);
    titleLabel->setObjectName(QStringLiteral("appTitle"));
    QLabel* subtitleLabel = new QLabel(topBar);
    subtitleLabel->setObjectName(QStringLiteral("muted"));

    QPushButton* settingsButton = new QPushButton(topBar);
    settingsButton->setCheckable(true);
    QPushButton* addButton = new QPushButton(topBar);
    addButton->setCheckable(true);
    QPushButton* editButton = new QPushButton(topBar);
    editButton->setCheckable(true);
    QPushButton* sortButton = new QPushButton(topBar);
    sortButton->setCheckable(true);
    QPushButton* fileButton = new QPushButton(topBar);
    fileButton->setCheckable(true);

    topLayout->addWidget(logoFrame, 0, 0, 2, 1);
    topLayout->addWidget(titleLabel, 0, 1);
    topLayout->addWidget(subtitleLabel, 1, 1);
    topLayout->addWidget(settingsButton, 0, 2, 2, 1);
    topLayout->addWidget(addButton, 0, 3, 2, 1);
    topLayout->addWidget(editButton, 0, 4, 2, 1);
    topLayout->addWidget(sortButton, 0, 5, 2, 1);
    topLayout->addWidget(fileButton, 0, 6, 2, 1);
    topLayout->setColumnStretch(1, 1);

    QFrame* actionPanel = new QFrame(rootWidget);
    actionPanel->setObjectName(QStringLiteral("actionPanel"));
    QVBoxLayout* actionPanelLayout = new QVBoxLayout(actionPanel);
    actionPanelLayout->setContentsMargins(16, 14, 16, 14);

    QStackedWidget* actionStack = new QStackedWidget(actionPanel);
    actionPanelLayout->addWidget(actionStack);
    actionPanel->hide();

    QWidget* settingsPage = new QWidget(actionStack);
    QGridLayout* settingsLayout = new QGridLayout(settingsPage);
    QComboBox* themeComboBox = new QComboBox(settingsPage);
    QComboBox* languageComboBox = new QComboBox(settingsPage);
    QLabel* themeLabel = new QLabel(settingsPage);
    QLabel* languageLabel = new QLabel(settingsPage);
    settingsLayout->addWidget(themeLabel, 0, 0);
    settingsLayout->addWidget(themeComboBox, 0, 1);
    settingsLayout->addWidget(languageLabel, 0, 2);
    settingsLayout->addWidget(languageComboBox, 0, 3);
    settingsLayout->setColumnStretch(4, 1);

    QWidget* addPage = new QWidget(actionStack);
    QGridLayout* addLayout = new QGridLayout(addPage);
    QLineEdit* addNameEdit = new QLineEdit(addPage);
    QDoubleSpinBox* addPriceSpinBox = new QDoubleSpinBox(addPage);
    QSpinBox* addQuantitySpinBox = new QSpinBox(addPage);
    QPushButton* addSubmitButton = new QPushButton(addPage);
    addSubmitButton->setObjectName(QStringLiteral("primaryButton"));
    addPriceSpinBox->setRange(0.01, 1000000.0);
    addPriceSpinBox->setDecimals(2);
    addPriceSpinBox->setValue(1.0);
    addPriceSpinBox->setMinimumWidth(150);
    addQuantitySpinBox->setRange(0, 1000000);
    addQuantitySpinBox->setValue(1);
    addQuantitySpinBox->setMinimumWidth(150);
    addLayout->addWidget(addNameEdit, 0, 0);
    addLayout->addWidget(addPriceSpinBox, 0, 1);
    addLayout->addWidget(addQuantitySpinBox, 0, 2);
    addLayout->addWidget(addSubmitButton, 0, 3);
    addLayout->setColumnStretch(0, 1);

    QWidget* editPage = new QWidget(actionStack);
    QGridLayout* editLayout = new QGridLayout(editPage);
    QLabel* editSelectedLabel = new QLabel(editPage);
    QSpinBox* editQuantitySpinBox = new QSpinBox(editPage);
    QPushButton* updateQuantityButton = new QPushButton(editPage);
    updateQuantityButton->setObjectName(QStringLiteral("primaryButton"));
    QPushButton* deleteProductButton = new QPushButton(editPage);
    deleteProductButton->setObjectName(QStringLiteral("dangerButton"));
    editQuantitySpinBox->setRange(0, 1000000);
    editQuantitySpinBox->setMinimumWidth(150);
    editLayout->addWidget(editSelectedLabel, 0, 0);
    editLayout->addWidget(editQuantitySpinBox, 0, 1);
    editLayout->addWidget(updateQuantityButton, 0, 2);
    editLayout->addWidget(deleteProductButton, 0, 3);
    editLayout->setColumnStretch(0, 1);

    QWidget* sortPage = new QWidget(actionStack);
    QGridLayout* sortLayout = new QGridLayout(sortPage);
    QLabel* sortFieldLabel = new QLabel(sortPage);
    QLabel* sortAlgorithmLabel = new QLabel(sortPage);
    QComboBox* sortFieldComboBox = new QComboBox(sortPage);
    QComboBox* sortAlgorithmComboBox = new QComboBox(sortPage);
    QPushButton* applySortButton = new QPushButton(sortPage);
    applySortButton->setObjectName(QStringLiteral("primaryButton"));
    sortLayout->addWidget(sortFieldLabel, 0, 0);
    sortLayout->addWidget(sortFieldComboBox, 0, 1);
    sortLayout->addWidget(sortAlgorithmLabel, 0, 2);
    sortLayout->addWidget(sortAlgorithmComboBox, 0, 3);
    sortLayout->addWidget(applySortButton, 0, 4);
    sortLayout->setColumnStretch(5, 1);

    QWidget* filePage = new QWidget(actionStack);
    QGridLayout* fileLayout = new QGridLayout(filePage);
    QLabel* totalValuePanelLabel = new QLabel(filePage);
    QPushButton* saveButton = new QPushButton(filePage);
    saveButton->setObjectName(QStringLiteral("primaryButton"));
    QPushButton* reloadButton = new QPushButton(filePage);
    fileLayout->addWidget(totalValuePanelLabel, 0, 0);
    fileLayout->addWidget(saveButton, 0, 1);
    fileLayout->addWidget(reloadButton, 0, 2);
    fileLayout->setColumnStretch(3, 1);

    actionStack->addWidget(settingsPage);
    actionStack->addWidget(addPage);
    actionStack->addWidget(editPage);
    actionStack->addWidget(sortPage);
    actionStack->addWidget(filePage);

    QWidget* contentWidget = new QWidget(rootWidget);
    QGridLayout* contentLayout = new QGridLayout(contentWidget);
    contentLayout->setContentsMargins(0, 0, 0, 0);
    contentLayout->setHorizontalSpacing(14);
    contentLayout->setVerticalSpacing(12);

    QLineEdit* searchNameEdit = new QLineEdit(contentWidget);
    QLineEdit* quantityFilterEdit = new QLineEdit(contentWidget);
    QPushButton* clearFiltersButton = new QPushButton(contentWidget);
    quantityFilterEdit->setValidator(new QIntValidator(0, 1000000, quantityFilterEdit));

    QLabel* productsHeadingLabel = new QLabel(contentWidget);
    productsHeadingLabel->setObjectName(QStringLiteral("appTitle"));
    QLabel* totalValueLabel = new QLabel(contentWidget);
    totalValueLabel->setObjectName(QStringLiteral("muted"));

    QTableWidget* productsTable = new QTableWidget(contentWidget);
    productsTable->setColumnCount(4);
    productsTable->setAlternatingRowColors(true);
    productsTable->setSelectionBehavior(QAbstractItemView::SelectRows);
    productsTable->setSelectionMode(QAbstractItemView::ExtendedSelection);
    productsTable->setEditTriggers(QAbstractItemView::NoEditTriggers);
    productsTable->verticalHeader()->setVisible(false);
    productsTable->horizontalHeader()->setStretchLastSection(false);
    productsTable->horizontalHeader()->setSectionResizeMode(0, QHeaderView::ResizeToContents);
    productsTable->horizontalHeader()->setSectionResizeMode(1, QHeaderView::Stretch);
    productsTable->horizontalHeader()->setSectionResizeMode(2, QHeaderView::ResizeToContents);
    productsTable->horizontalHeader()->setSectionResizeMode(3, QHeaderView::ResizeToContents);

    QFrame* detailsCard = new QFrame(contentWidget);
    detailsCard->setObjectName(QStringLiteral("detailsCard"));
    QVBoxLayout* detailsLayout = new QVBoxLayout(detailsCard);
    detailsLayout->setContentsMargins(16, 16, 16, 16);
    QLabel* selectedTitleLabel = new QLabel(detailsCard);
    selectedTitleLabel->setObjectName(QStringLiteral("appTitle"));
    QLabel* selectedNameLabel = new QLabel(detailsCard);
    QLabel* selectedMetaLabel = new QLabel(detailsCard);
    selectedMetaLabel->setObjectName(QStringLiteral("muted"));
    QLabel* statusLabel = new QLabel(detailsCard);
    statusLabel->setObjectName(QStringLiteral("statusLabel"));
    statusLabel->setWordWrap(true);
    detailsLayout->addWidget(selectedTitleLabel);
    detailsLayout->addSpacing(8);
    detailsLayout->addWidget(selectedNameLabel);
    detailsLayout->addWidget(selectedMetaLabel);
    detailsLayout->addStretch(1);
    detailsLayout->addWidget(statusLabel);

    contentLayout->addWidget(productsHeadingLabel, 0, 0);
    contentLayout->addWidget(totalValueLabel, 0, 1);
    contentLayout->addWidget(searchNameEdit, 1, 0);
    contentLayout->addWidget(quantityFilterEdit, 1, 1);
    contentLayout->addWidget(clearFiltersButton, 1, 2);
    contentLayout->addWidget(productsTable, 2, 0, 1, 3);
    contentLayout->addWidget(detailsCard, 0, 3, 3, 1);
    contentLayout->setColumnStretch(0, 4);
    contentLayout->setColumnStretch(3, 1);
    contentLayout->setRowStretch(2, 1);

    rootLayout->addWidget(topBar);
    rootLayout->addWidget(actionPanel);
    rootLayout->addWidget(contentWidget, 1);
    window.setCentralWidget(rootWidget);

    for (const themeDefinition& theme : themes)
    {
        themeComboBox->addItem(theme.name);
    }

    for (const languageText& text : texts)
    {
        languageComboBox->addItem(text.languageName);
    }

    auto setStatus = [&](const QString& message)
    {
        statusLabel->setText(message);
        subtitleLabel->setText(
            QStringLiteral("%1: %2  |  %3")
                .arg(texts[currentLanguage].products)
                .arg(getProductCountForDisplay())
                .arg(message)
        );
    };

    auto refreshSelection = [&]()
    {
        const languageText& text = texts[currentLanguage];

        if (selectedIndexes.size() > 1)
        {
            float selectedValue = 0.0f;
            int selectedQuantity = 0;

            for (int index : selectedIndexes)
            {
                product selectedProduct = {};
                if (getProductForDisplay(index, &selectedProduct))
                {
                    selectedValue += selectedProduct.price * selectedProduct.quantity;
                    selectedQuantity += selectedProduct.quantity;
                }
            }

            selectedIndex = selectedIndexes.front();
            selectedNameLabel->setText(
                QStringLiteral("%1 %2").arg(selectedIndexes.size()).arg(text.products)
            );
            selectedMetaLabel->setText(
                QStringLiteral("%1: %2   %3: %4")
                    .arg(text.totalValue)
                    .arg(formatMoney(selectedValue))
                    .arg(text.quantity)
                    .arg(selectedQuantity)
            );
            editSelectedLabel->setText(
                QStringLiteral("%1 %2").arg(selectedIndexes.size()).arg(text.products)
            );
        }
        else if (selectedIndexes.size() == 1)
        {
            product selectedProduct = {};
            selectedIndex = selectedIndexes.front();

            if (getProductForDisplay(selectedIndex, &selectedProduct))
            {
                selectedNameLabel->setText(productDisplayName(selectedProduct));
                selectedMetaLabel->setText(
                    QStringLiteral("%1: %2   %3: %4")
                        .arg(text.price)
                        .arg(formatMoney(selectedProduct.price))
                        .arg(text.quantity)
                        .arg(selectedProduct.quantity)
                );
                editSelectedLabel->setText(productDisplayName(selectedProduct));
                editQuantitySpinBox->setValue(selectedProduct.quantity);
            }
        }
        else
        {
            selectedIndex = -1;
            selectedNameLabel->setText(text.noSelection);
            selectedMetaLabel->clear();
            editSelectedLabel->setText(text.noSelection);
            editQuantitySpinBox->setValue(0);
        }
    };

    auto refreshTotals = [&]()
    {
        const languageText& text = texts[currentLanguage];
        const QString totalText = QStringLiteral("%1: %2")
            .arg(text.totalValue)
            .arg(formatMoney(calculateInventoryTotalValue()));
        totalValueLabel->setText(totalText);
        totalValuePanelLabel->setText(totalText);
        subtitleLabel->setText(
            QStringLiteral("%1: %2  |  %3")
                .arg(text.products)
                .arg(getProductCountForDisplay())
                .arg(statusLabel->text())
        );
    };

    auto refreshTable = [&]()
    {
        const QSignalBlocker tableBlocker(productsTable);
        const QSignalBlocker selectionBlocker(productsTable->selectionModel());

        productsTable->setRowCount(0);
        productsTable->clearSelection();

        const QString nameFilter = searchNameEdit->text().trimmed();
        bool hasQuantityFilter = false;
        const int quantityFilter =
            quantityFilterEdit->text().trimmed().toInt(&hasQuantityFilter);
        int visibleRow = 0;

        for (int i = 0; i < getProductCountForDisplay(); ++i)
        {
            product item = {};
            getProductForDisplay(i, &item);

            const QString name = productDisplayName(item);
            if (!nameFilter.isEmpty()
                && !name.contains(nameFilter, Qt::CaseInsensitive))
            {
                continue;
            }

            if (hasQuantityFilter && item.quantity != quantityFilter)
            {
                continue;
            }

            productsTable->insertRow(visibleRow);

            QTableWidgetItem* numberItem =
                new QTableWidgetItem(QString::number(i + 1));
            numberItem->setData(Qt::UserRole, i);

            QTableWidgetItem* nameItem = new QTableWidgetItem(name);
            QTableWidgetItem* priceItem =
                new QTableWidgetItem(formatMoney(item.price));
            QTableWidgetItem* quantityItem =
                new QTableWidgetItem(QString::number(item.quantity));

            numberItem->setTextAlignment(Qt::AlignCenter);
            priceItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);
            quantityItem->setTextAlignment(Qt::AlignRight | Qt::AlignVCenter);

            productsTable->setItem(visibleRow, 0, numberItem);
            productsTable->setItem(visibleRow, 1, nameItem);
            productsTable->setItem(visibleRow, 2, priceItem);
            productsTable->setItem(visibleRow, 3, quantityItem);

            if (selectedIndexes.contains(i))
            {
                productsTable->selectionModel()->select(
                    productsTable->model()->index(visibleRow, 0),
                    QItemSelectionModel::Select | QItemSelectionModel::Rows
                );
            }

            ++visibleRow;
        }

        if (visibleRow == 0)
        {
            productsTable->setRowCount(1);
            QTableWidgetItem* emptyItem =
                new QTableWidgetItem(texts[currentLanguage].noProducts);
            emptyItem->setTextAlignment(Qt::AlignCenter);
            productsTable->setItem(0, 1, emptyItem);
        }

        refreshTotals();
        refreshSelection();
    };

    auto applyLanguage = [&]()
    {
        const languageText& text = texts[currentLanguage];

        window.setWindowTitle(text.windowTitle);
        settingsButton->setText(text.settings);
        addButton->setText(text.addProduct);
        editButton->setText(text.editProduct);
        sortButton->setText(text.sortProducts);
        fileButton->setText(text.file);

        themeLabel->setText(text.theme);
        languageLabel->setText(text.language);
        addNameEdit->setPlaceholderText(text.productName);
        addPriceSpinBox->setPrefix(text.price + QStringLiteral(": "));
        addQuantitySpinBox->setPrefix(text.quantity + QStringLiteral(": "));
        addSubmitButton->setText(text.add);

        updateQuantityButton->setText(text.updateQuantity);
        deleteProductButton->setText(text.deleteProduct);
        editQuantitySpinBox->setPrefix(text.quantity + QStringLiteral(": "));

        sortFieldLabel->setText(text.sortField);
        sortAlgorithmLabel->setText(text.sortAlgorithm);
        sortFieldComboBox->clear();
        sortFieldComboBox->addItems({ text.sortByPrice, text.sortByQuantity });
        sortAlgorithmComboBox->clear();
        sortAlgorithmComboBox->addItems({ text.quickSort, text.bogoSort });
        applySortButton->setText(text.applySort);

        saveButton->setText(text.save);
        reloadButton->setText(text.reload);
        productsHeadingLabel->setText(text.products);
        searchNameEdit->setPlaceholderText(text.searchName);
        quantityFilterEdit->setPlaceholderText(
            text.exactQuantity + QStringLiteral(" (blank = all)")
        );
        clearFiltersButton->setText(text.clearFilters);
        selectedTitleLabel->setText(text.selectedProduct);

        productsTable->setHorizontalHeaderLabels(
            { QStringLiteral("#"), text.productName, text.price, text.quantity }
        );

        if (statusLabel->text().isEmpty())
        {
            setStatus(text.ready);
        }

        refreshTable();
    };

    auto showPanel = [&](int panelIndex, QPushButton* activeButton)
    {
        const QList<QPushButton*> navButtons = {
            settingsButton, addButton, editButton, sortButton, fileButton
        };

        const bool shouldHide =
            actionPanel->isVisible() && actionStack->currentIndex() == panelIndex;

        for (QPushButton* button : navButtons)
        {
            button->setChecked(false);
        }

        if (shouldHide)
        {
            actionPanel->hide();
            return;
        }

        actionStack->setCurrentIndex(panelIndex);
        actionPanel->show();
        activeButton->setChecked(true);
    };

    QObject::connect(settingsButton, &QPushButton::clicked, [&]()
    {
        showPanel(0, settingsButton);
    });

    QObject::connect(addButton, &QPushButton::clicked, [&]()
    {
        showPanel(1, addButton);
    });

    QObject::connect(editButton, &QPushButton::clicked, [&]()
    {
        showPanel(2, editButton);
    });

    QObject::connect(sortButton, &QPushButton::clicked, [&]()
    {
        showPanel(3, sortButton);
    });

    QObject::connect(fileButton, &QPushButton::clicked, [&]()
    {
        showPanel(4, fileButton);
    });

    QObject::connect(themeComboBox, &QComboBox::currentIndexChanged, [&](int index)
    {
        if (index >= 0 && index < themes.size())
        {
            currentTheme = index;
            app.setStyleSheet(createStyleSheet(themes[currentTheme]));
        }
    });

    QObject::connect(languageComboBox, &QComboBox::currentIndexChanged, [&](int index)
    {
        if (index >= 0 && index < texts.size())
        {
            currentLanguage = index;
            applyLanguage();
        }
    });

    QObject::connect(searchNameEdit, &QLineEdit::textChanged, [&]()
    {
        refreshTable();
    });

    QObject::connect(quantityFilterEdit, &QLineEdit::textChanged, [&]()
    {
        refreshTable();
    });

    QObject::connect(clearFiltersButton, &QPushButton::clicked, [&]()
    {
        searchNameEdit->clear();
        quantityFilterEdit->clear();
        refreshTable();
    });

    QObject::connect(
        productsTable->selectionModel(),
        &QItemSelectionModel::selectionChanged,
        [&]()
    {
        selectedIndexes.clear();

        const QModelIndexList selectedRows =
            productsTable->selectionModel()->selectedRows();

        for (const QModelIndex& rowIndex : selectedRows)
        {
            QTableWidgetItem* indexItem = productsTable->item(rowIndex.row(), 0);
            if (indexItem != nullptr && indexItem->data(Qt::UserRole).isValid())
            {
                selectedIndexes.push_back(indexItem->data(Qt::UserRole).toInt());
            }
        }

        std::sort(selectedIndexes.begin(), selectedIndexes.end());
        selectedIndex = selectedIndexes.isEmpty() ? -1 : selectedIndexes.front();
        refreshSelection();
    });

    QObject::connect(addSubmitButton, &QPushButton::clicked, [&]()
    {
        product item = {};
        copyToProductName(&item, addNameEdit->text());
        item.price = static_cast<float>(addPriceSpinBox->value());
        item.quantity = addQuantitySpinBox->value();

        if (addNewProduct(item.name, item.price, item.quantity))
        {
            addNameEdit->clear();
            addPriceSpinBox->setValue(1.0);
            addQuantitySpinBox->setValue(1);
            setStatus(texts[currentLanguage].productAdded);
            refreshTable();
        }
        else
        {
            setStatus(texts[currentLanguage].invalidInput);
        }
    });

    QObject::connect(updateQuantityButton, &QPushButton::clicked, [&]()
    {
        if (selectedIndexes.isEmpty())
        {
            setStatus(texts[currentLanguage].noSelection);
            return;
        }

        bool updated = true;
        for (int index : selectedIndexes)
        {
            updated = updateProductQuantity(index, editQuantitySpinBox->value())
                && updated;
        }

        if (updated)
        {
            setStatus(texts[currentLanguage].quantityUpdated);
            refreshTable();
        }
        else
        {
            setStatus(texts[currentLanguage].invalidInput);
        }
    });

    QObject::connect(deleteProductButton, &QPushButton::clicked, [&]()
    {
        if (selectedIndexes.isEmpty())
        {
            setStatus(texts[currentLanguage].noSelection);
            return;
        }

        const QMessageBox::StandardButton answer = QMessageBox::question(
            &window,
            texts[currentLanguage].confirmDeleteTitle,
            texts[currentLanguage].confirmDeleteText
        );

        if (answer == QMessageBox::Yes)
        {
            std::sort(selectedIndexes.begin(), selectedIndexes.end(), std::greater<int>());

            bool deleted = true;
            for (int index : selectedIndexes)
            {
                deleted = deleteProductByIndex(index) && deleted;
            }

            selectedIndex = -1;
            selectedIndexes.clear();
            setStatus(deleted
                ? texts[currentLanguage].productDeleted
                : texts[currentLanguage].invalidInput);
            refreshTable();
        }
    });

    QObject::connect(applySortButton, &QPushButton::clicked, [&]()
    {
        const bool sorted = sortInventory(
            sortFieldComboBox->currentIndex() == 0 ? sortByPrice : sortByQuantity,
            sortAlgorithmComboBox->currentIndex() == 0
                ? quickSortAlgorithm
                : bogoSortAlgorithm
        );

        selectedIndex = -1;
        selectedIndexes.clear();
        setStatus(sorted ? texts[currentLanguage].sorted : texts[currentLanguage].bogoBlocked);
        refreshTable();
    });

    QObject::connect(saveButton, &QPushButton::clicked, [&]()
    {
        setStatus(
            saveInventoryToFile(inventoryFilePath)
                ? texts[currentLanguage].saved
                : texts[currentLanguage].invalidInput
        );
    });

    QObject::connect(reloadButton, &QPushButton::clicked, [&]()
    {
        selectedIndex = -1;
        selectedIndexes.clear();
        setStatus(
            loadInventoryFromFile(inventoryFilePath)
                ? texts[currentLanguage].loaded
                : texts[currentLanguage].invalidInput
        );
        refreshTable();
    });

    themeComboBox->setCurrentIndex(currentTheme);
    languageComboBox->setCurrentIndex(currentLanguage);
    app.setStyleSheet(createStyleSheet(themes[currentTheme]));
    applyLanguage();
    setStatus(texts[currentLanguage].ready);
    refreshTable();

    window.show();
    app.exec();
}
