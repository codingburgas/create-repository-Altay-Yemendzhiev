#include "../include/presentation.h"

#include "../include/logic.h"

#include "imgui.h"
#include "imgui_impl_dx11.h"
#include "imgui_impl_win32.h"

#include <d3d11.h>
#include <tchar.h>
#include <windows.h>

#include <cstdio>
#include <cstring>

static ID3D11Device* d3dDevice = nullptr;
static ID3D11DeviceContext* d3dDeviceContext = nullptr;
static IDXGISwapChain* swapChain = nullptr;
static ID3D11RenderTargetView* mainRenderTargetView = nullptr;

extern IMGUI_IMPL_API LRESULT ImGui_ImplWin32_WndProcHandler(
    HWND window,
    UINT message,
    WPARAM wordParam,
    LPARAM longParam
);

enum language
{
    bulgarianLanguage,
    spanishLanguage,
    frenchLanguage,
    germanLanguage,
    englishLanguage,
    turkishLanguage,
    languageCount
};

enum appTheme
{
    calmNightTheme,
    softSnowTheme,
    blueBellTheme,
    graphiteBloomTheme,
    themeCount
};

struct themePalette
{
    const char* name;
    ImVec4 text;
    ImVec4 mutedText;
    ImVec4 window;
    ImVec4 panel;
    ImVec4 panelAlt;
    ImVec4 border;
    ImVec4 field;
    ImVec4 button;
    ImVec4 buttonHover;
    ImVec4 accent;
    ImVec4 tableHeader;
    ImVec4 row;
    ImVec4 rowAlt;
    ImVec4 selection;
};

struct uiText
{
    const char* languageName;
    const char* title;
    const char* products;
    const char* controls;
    const char* addProduct;
    const char* productName;
    const char* price;
    const char* quantity;
    const char* add;
    const char* updateQuantity;
    const char* deleteProduct;
    const char* searchName;
    const char* searchQuantity;
    const char* exactQuantity;
    const char* clearFilters;
    const char* sortProducts;
    const char* sortField;
    const char* sortAlgorithm;
    const char* sortByPrice;
    const char* sortByQuantity;
    const char* quickSort;
    const char* bogoSort;
    const char* applySort;
    const char* totalValue;
    const char* save;
    const char* reload;
    const char* theme;
    const char* dark;
    const char* light;
    const char* languageLabel;
    const char* status;
    const char* selectRow;
    const char* invalidInput;
    const char* productAdded;
    const char* quantityUpdated;
    const char* productDeleted;
    const char* sorted;
    const char* bogoBlocked;
    const char* saved;
    const char* loaded;
    const char* noProducts;
};

static const uiText texts[languageCount] = {
    {
        u8"Български", u8"Система за управление на магазин", u8"Продукти",
        u8"Управление", u8"Добави продукт", u8"Име на продукт", u8"Цена",
        u8"Количество", u8"Добави", u8"Обнови количество", u8"Изтрий продукт",
        u8"Търсене по име", u8"Търсене по количество", u8"Точно количество",
        u8"Изчисти",
        u8"Сортиране", u8"Поле", u8"Алгоритъм", u8"Цена", u8"Количество",
        u8"Бързо сортиране", u8"Бого сортиране", u8"Сортирай",
        u8"Обща стойност", u8"Запази", u8"Презареди", u8"Тема", u8"Тъмна",
        u8"Светла", u8"Език", u8"Състояние", u8"Изберете ред от таблицата.",
        u8"Невалидни данни.", u8"Продуктът е добавен.",
        u8"Количеството е обновено.", u8"Продуктът е изтрит.",
        u8"Продуктите са сортирани.",
        u8"Бого сортиране е блокирано за повече от 8 продукта.",
        u8"Данните са запазени.", u8"Данните са заредени.", u8"Няма продукти."
    },
    {
        u8"Español", u8"Sistema de inventario", u8"Productos", u8"Controles",
        u8"Añadir producto", u8"Nombre del producto", u8"Precio", u8"Cantidad",
        u8"Añadir", u8"Actualizar cantidad", u8"Eliminar producto",
        u8"Buscar por nombre", u8"Buscar por cantidad", u8"Cantidad exacta",
        u8"Limpiar",
        u8"Ordenar productos", u8"Campo", u8"Algoritmo", u8"Precio",
        u8"Cantidad", u8"Quick Sort", u8"Bogo Sort", u8"Ordenar",
        u8"Valor total", u8"Guardar", u8"Recargar", u8"Tema", u8"Oscuro",
        u8"Claro", u8"Idioma", u8"Estado", u8"Selecciona una fila.",
        u8"Datos no válidos.", u8"Producto añadido.",
        u8"Cantidad actualizada.", u8"Producto eliminado.",
        u8"Productos ordenados.",
        u8"Bogo Sort está bloqueado para más de 8 productos.",
        u8"Datos guardados.", u8"Datos cargados.", u8"No hay productos."
    },
    {
        u8"Français", u8"Système d'inventaire", u8"Produits", u8"Contrôles",
        u8"Ajouter un produit", u8"Nom du produit", u8"Prix", u8"Quantité",
        u8"Ajouter", u8"Mettre à jour", u8"Supprimer",
        u8"Recherche par nom", u8"Recherche par quantité", u8"Quantité exacte",
        u8"Effacer",
        u8"Trier les produits", u8"Champ", u8"Algorithme", u8"Prix",
        u8"Quantité", u8"Tri rapide", u8"Tri bogo", u8"Trier",
        u8"Valeur totale", u8"Enregistrer", u8"Recharger", u8"Thème",
        u8"Sombre", u8"Clair", u8"Langue", u8"État",
        u8"Sélectionnez une ligne.", u8"Données invalides.",
        u8"Produit ajouté.", u8"Quantité mise à jour.", u8"Produit supprimé.",
        u8"Produits triés.",
        u8"Le tri bogo est bloqué pour plus de 8 produits.",
        u8"Données enregistrées.", u8"Données chargées.", u8"Aucun produit."
    },
    {
        u8"Deutsch", u8"Lagerverwaltung", u8"Produkte", u8"Steuerung",
        u8"Produkt hinzufügen", u8"Produktname", u8"Preis", u8"Menge",
        u8"Hinzufügen", u8"Menge aktualisieren", u8"Produkt löschen",
        u8"Nach Name suchen", u8"Nach Menge suchen", u8"Genaue Menge",
        u8"Leeren",
        u8"Produkte sortieren", u8"Feld", u8"Algorithmus", u8"Preis",
        u8"Menge", u8"Quick Sort", u8"Bogo Sort", u8"Sortieren",
        u8"Gesamtwert", u8"Speichern", u8"Neu laden", u8"Design", u8"Dunkel",
        u8"Hell", u8"Sprache", u8"Status", u8"Wähle eine Zeile aus.",
        u8"Ungültige Daten.", u8"Produkt hinzugefügt.",
        u8"Menge aktualisiert.", u8"Produkt gelöscht.", u8"Produkte sortiert.",
        u8"Bogo Sort ist bei mehr als 8 Produkten blockiert.",
        u8"Daten gespeichert.", u8"Daten geladen.", u8"Keine Produkte."
    },
    {
        "English", "Inventory management system", "Products", "Controls",
        "Add product", "Product name", "Price", "Quantity", "Add",
        "Update quantity", "Delete product", "Search by name",
        "Search by quantity", "Exact quantity", "Clear", "Sort products", "Field",
        "Algorithm", "Price", "Quantity", "Quick Sort", "Bogo Sort",
        "Sort", "Total value", "Save", "Reload", "Theme", "Dark", "Light",
        "Language", "Status", "Select a row from the table.", "Invalid data.",
        "Product added.", "Quantity updated.", "Product deleted.",
        "Products sorted.", "Bogo Sort is blocked for more than 8 products.",
        "Data saved.", "Data loaded.", "No products."
    },
    {
        u8"Türkçe", u8"Envanter yönetim sistemi", u8"Ürünler", u8"Kontroller",
        u8"Ürün ekle", u8"Ürün adı", u8"Fiyat", u8"Adet", u8"Ekle",
        u8"Adedi güncelle", u8"Ürünü sil", u8"Ada göre ara",
        u8"Adede göre ara", u8"Tam adet", u8"Temizle",
        u8"Ürünleri sırala", u8"Alan",
        u8"Algoritma", u8"Fiyat", u8"Adet", u8"Hızlı sıralama",
        u8"Bogo sıralama", u8"Sırala", u8"Toplam değer", u8"Kaydet",
        u8"Yeniden yükle", u8"Tema", u8"Koyu", u8"Açık", u8"Dil", u8"Durum",
        u8"Tablodan bir satır seçin.", u8"Geçersiz veri.",
        u8"Ürün eklendi.", u8"Adet güncellendi.", u8"Ürün silindi.",
        u8"Ürünler sıralandı.",
        u8"Bogo sıralama 8 üründen fazlası için engellendi.",
        u8"Veriler kaydedildi.", u8"Veriler yüklendi.", u8"Ürün yok."
    }
};

static bool createDeviceD3D(HWND window)
{
    DXGI_SWAP_CHAIN_DESC swapChainDescription = {};
    swapChainDescription.BufferCount = 2;
    swapChainDescription.BufferDesc.Format = DXGI_FORMAT_R8G8B8A8_UNORM;
    swapChainDescription.BufferDesc.RefreshRate.Numerator = 60;
    swapChainDescription.BufferDesc.RefreshRate.Denominator = 1;
    swapChainDescription.Flags = DXGI_SWAP_CHAIN_FLAG_ALLOW_MODE_SWITCH;
    swapChainDescription.BufferUsage = DXGI_USAGE_RENDER_TARGET_OUTPUT;
    swapChainDescription.OutputWindow = window;
    swapChainDescription.SampleDesc.Count = 1;
    swapChainDescription.Windowed = TRUE;
    swapChainDescription.SwapEffect = DXGI_SWAP_EFFECT_DISCARD;

    const D3D_FEATURE_LEVEL featureLevelArray[2] = {
        D3D_FEATURE_LEVEL_11_0,
        D3D_FEATURE_LEVEL_10_0
    };
    D3D_FEATURE_LEVEL featureLevel = D3D_FEATURE_LEVEL_11_0;

    const HRESULT result = D3D11CreateDeviceAndSwapChain(
        nullptr,
        D3D_DRIVER_TYPE_HARDWARE,
        nullptr,
        0,
        featureLevelArray,
        2,
        D3D11_SDK_VERSION,
        &swapChainDescription,
        &swapChain,
        &d3dDevice,
        &featureLevel,
        &d3dDeviceContext
    );

    return result == S_OK;
}

static void createRenderTarget()
{
    ID3D11Texture2D* backBuffer = nullptr;
    swapChain->GetBuffer(0, IID_PPV_ARGS(&backBuffer));
    d3dDevice->CreateRenderTargetView(backBuffer, nullptr, &mainRenderTargetView);
    backBuffer->Release();
}

static void cleanupRenderTarget()
{
    if (mainRenderTargetView != nullptr)
    {
        mainRenderTargetView->Release();
        mainRenderTargetView = nullptr;
    }
}

static void cleanupDeviceD3D()
{
    cleanupRenderTarget();

    if (swapChain != nullptr)
    {
        swapChain->Release();
        swapChain = nullptr;
    }

    if (d3dDeviceContext != nullptr)
    {
        d3dDeviceContext->Release();
        d3dDeviceContext = nullptr;
    }

    if (d3dDevice != nullptr)
    {
        d3dDevice->Release();
        d3dDevice = nullptr;
    }
}

static LRESULT WINAPI windowProcedure(
    HWND window,
    UINT message,
    WPARAM wordParam,
    LPARAM longParam
)
{
    if (ImGui_ImplWin32_WndProcHandler(window, message, wordParam, longParam))
    {
        return true;
    }

    switch (message)
    {
    case WM_SIZE:
        if (wordParam != SIZE_MINIMIZED && d3dDevice != nullptr)
        {
            cleanupRenderTarget();
            swapChain->ResizeBuffers(
                0,
                LOWORD(longParam),
                HIWORD(longParam),
                DXGI_FORMAT_UNKNOWN,
                0
            );
            createRenderTarget();
        }
        return 0;
    case WM_SYSCOMMAND:
        if ((wordParam & 0xfff0) == SC_KEYMENU)
        {
            return 0;
        }
        break;
    case WM_DESTROY:
        PostQuitMessage(0);
        return 0;
    default:
        break;
    }

    return DefWindowProcW(window, message, wordParam, longParam);
}

static ImVec4 colorFromHex(int red, int green, int blue, float alpha = 1.0f)
{
    return ImVec4(red / 255.0f, green / 255.0f, blue / 255.0f, alpha);
}

static const themePalette themePalettes[themeCount] = {
    {
        "calm night",
        colorFromHex(0xff, 0xfa, 0xff),
        colorFromHex(0xb9, 0xc7, 0xd9),
        colorFromHex(0x16, 0x1b, 0x26),
        colorFromHex(0x20, 0x28, 0x35),
        colorFromHex(0x25, 0x31, 0x42),
        colorFromHex(0x3e, 0x92, 0xcc, 0.25f),
        colorFromHex(0x2c, 0x36, 0x47),
        colorFromHex(0x2d, 0x68, 0x95),
        colorFromHex(0x3e, 0x92, 0xcc),
        colorFromHex(0xd8, 0x31, 0x5b, 0.82f),
        colorFromHex(0x25, 0x3f, 0x67),
        colorFromHex(0x1d, 0x24, 0x31),
        colorFromHex(0x22, 0x2b, 0x3a),
        colorFromHex(0x3e, 0x92, 0xcc, 0.30f)
    },
    {
        "soft snow",
        colorFromHex(0x1e, 0x1b, 0x18),
        colorFromHex(0x68, 0x71, 0x7d),
        colorFromHex(0xff, 0xfa, 0xff),
        colorFromHex(0xf4, 0xf7, 0xfb),
        colorFromHex(0xea, 0xf2, 0xf8),
        colorFromHex(0x0a, 0x24, 0x63, 0.16f),
        colorFromHex(0xff, 0xff, 0xff),
        colorFromHex(0x72, 0xae, 0xd5),
        colorFromHex(0x3e, 0x92, 0xcc),
        colorFromHex(0xd8, 0x31, 0x5b, 0.70f),
        colorFromHex(0xd9, 0xe8, 0xf3),
        colorFromHex(0xff, 0xff, 0xff),
        colorFromHex(0xf1, 0xf6, 0xfa),
        colorFromHex(0x3e, 0x92, 0xcc, 0.20f)
    },
    {
        "blue bell",
        colorFromHex(0x1e, 0x1b, 0x18),
        colorFromHex(0x58, 0x66, 0x72),
        colorFromHex(0xf7, 0xfb, 0xff),
        colorFromHex(0xe9, 0xf3, 0xfa),
        colorFromHex(0xdc, 0xec, 0xf5),
        colorFromHex(0x3e, 0x92, 0xcc, 0.24f),
        colorFromHex(0xff, 0xff, 0xff),
        colorFromHex(0x5b, 0xa0, 0xcd),
        colorFromHex(0x3e, 0x92, 0xcc),
        colorFromHex(0xd8, 0x31, 0x5b, 0.62f),
        colorFromHex(0xc9, 0xe2, 0xf1),
        colorFromHex(0xf9, 0xfc, 0xff),
        colorFromHex(0xed, 0xf5, 0xfa),
        colorFromHex(0x0a, 0x24, 0x63, 0.16f)
    },
    {
        "graphite bloom",
        colorFromHex(0xf7, 0xf1, 0xf5),
        colorFromHex(0xc8, 0xbd, 0xc4),
        colorFromHex(0x1e, 0x1b, 0x18),
        colorFromHex(0x2b, 0x27, 0x25),
        colorFromHex(0x34, 0x2e, 0x31),
        colorFromHex(0xd8, 0x31, 0x5b, 0.22f),
        colorFromHex(0x37, 0x32, 0x31),
        colorFromHex(0x8f, 0x3d, 0x59),
        colorFromHex(0xb8, 0x4e, 0x6e),
        colorFromHex(0x3e, 0x92, 0xcc, 0.74f),
        colorFromHex(0x3b, 0x32, 0x39),
        colorFromHex(0x26, 0x22, 0x20),
        colorFromHex(0x2e, 0x28, 0x28),
        colorFromHex(0xd8, 0x31, 0x5b, 0.24f)
    }
};

static void applyAppTheme(int themeIndex)
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 8.0f;
    style.ChildRounding = 8.0f;
    style.FrameRounding = 6.0f;
    style.PopupRounding = 8.0f;
    style.ScrollbarRounding = 8.0f;
    style.GrabRounding = 6.0f;
    style.WindowBorderSize = 1.0f;
    style.ChildBorderSize = 1.0f;
    style.FrameBorderSize = 1.0f;
    style.ItemSpacing = ImVec2(10.0f, 9.0f);
    style.WindowPadding = ImVec2(18.0f, 16.0f);
    style.FramePadding = ImVec2(11.0f, 7.0f);
    style.CellPadding = ImVec2(12.0f, 9.0f);

    const themePalette& palette = themePalettes[themeIndex];

    ImVec4* colors = style.Colors;
    colors[ImGuiCol_Text] = palette.text;
    colors[ImGuiCol_TextDisabled] = palette.mutedText;
    colors[ImGuiCol_WindowBg] = palette.window;
    colors[ImGuiCol_ChildBg] = palette.panel;
    colors[ImGuiCol_PopupBg] = palette.panel;
    colors[ImGuiCol_Border] = palette.border;
    colors[ImGuiCol_FrameBg] = palette.field;
    colors[ImGuiCol_FrameBgHovered] = palette.panelAlt;
    colors[ImGuiCol_FrameBgActive] = palette.selection;
    colors[ImGuiCol_TitleBg] = palette.panel;
    colors[ImGuiCol_TitleBgActive] = palette.panel;
    colors[ImGuiCol_MenuBarBg] = palette.panel;
    colors[ImGuiCol_Button] = palette.button;
    colors[ImGuiCol_ButtonHovered] = palette.buttonHover;
    colors[ImGuiCol_ButtonActive] = palette.accent;
    colors[ImGuiCol_Header] = palette.selection;
    colors[ImGuiCol_HeaderHovered] = palette.buttonHover;
    colors[ImGuiCol_HeaderActive] = palette.accent;
    colors[ImGuiCol_CheckMark] = palette.accent;
    colors[ImGuiCol_SliderGrab] = palette.button;
    colors[ImGuiCol_SliderGrabActive] = palette.accent;
    colors[ImGuiCol_TableHeaderBg] = palette.tableHeader;
    colors[ImGuiCol_TableRowBg] = palette.row;
    colors[ImGuiCol_TableRowBgAlt] = palette.rowAlt;
    colors[ImGuiCol_NavHighlight] = palette.selection;
    colors[ImGuiCol_Separator] = palette.border;
}

static void loadInterfaceFont()
{
    ImGuiIO& io = ImGui::GetIO();
    ImFontGlyphRangesBuilder builder;
    builder.AddRanges(io.Fonts->GetGlyphRangesDefault());
    builder.AddRanges(io.Fonts->GetGlyphRangesCyrillic());
    builder.AddText(
        u8"áéíóúñçàèùâêîôûäöüßğışİçŞĞÜÖ"
        u8"БългарскиСистемауправлениенамагазинПродуктиКоличество"
    );

    static ImVector<ImWchar> ranges;
    builder.BuildRanges(&ranges);

    ImFont* font = io.Fonts->AddFontFromFileTTF(
        "C:\\Windows\\Fonts\\segoeui.ttf",
        18.0f,
        nullptr,
        ranges.Data
    );

    if (font == nullptr)
    {
        io.Fonts->AddFontDefault();
    }
}

static void copyText(char destination[maxNameLength], const char* source)
{
    std::strncpy(destination, source, maxNameLength - 1);
    destination[maxNameLength - 1] = '\0';
}

static void renderProductsTable(
    int* selectedIndex,
    int* editQuantity,
    const char* nameFilter,
    int quantityFilter,
    const uiText& t
)
{
    const int productCount = getProductCountForDisplay();

    if (productCount == 0)
    {
        ImGui::TextUnformatted(t.noProducts);
        return;
    }

    if (ImGui::BeginTable(
        "productsTable",
        4,
        ImGuiTableFlags_RowBg
            | ImGuiTableFlags_BordersOuter
            | ImGuiTableFlags_BordersInnerH
            | ImGuiTableFlags_Resizable
            | ImGuiTableFlags_Reorderable
            | ImGuiTableFlags_ScrollY,
        ImVec2(0.0f, 0.0f)
    ))
    {
        ImGui::TableSetupColumn("#", ImGuiTableColumnFlags_WidthFixed, 44.0f);
        ImGui::TableSetupColumn(t.productName);
        ImGui::TableSetupColumn(t.price, ImGuiTableColumnFlags_WidthFixed, 90.0f);
        ImGui::TableSetupColumn(t.quantity, ImGuiTableColumnFlags_WidthFixed, 100.0f);
        ImGui::TableHeadersRow();

        for (int i = 0; i < productCount; ++i)
        {
            product item = {};
            getProductForDisplay(i, &item);

            if (nameFilter[0] != '\0' && std::strstr(item.name, nameFilter) == nullptr)
            {
                continue;
            }

            if (quantityFilter >= 0 && item.quantity != quantityFilter)
            {
                continue;
            }

            ImGui::TableNextRow();
            ImGui::TableSetColumnIndex(0);

            const bool isSelected = *selectedIndex == i;
            char label[32] = "";
            std::snprintf(label, sizeof(label), "%d", i + 1);

            if (ImGui::Selectable(
                label,
                isSelected,
                ImGuiSelectableFlags_SpanAllColumns
            ))
            {
                *selectedIndex = i;
                *editQuantity = item.quantity;
            }

            ImGui::TableSetColumnIndex(1);
            ImGui::TextUnformatted(item.name);
            ImGui::TableSetColumnIndex(2);
            ImGui::Text("%.2f", item.price);
            ImGui::TableSetColumnIndex(3);
            ImGui::Text("%d", item.quantity);
        }

        ImGui::EndTable();
    }
}

static void renderLocalizedCombo(
    const char* label,
    int* selectedIndex,
    const char* firstItem,
    const char* secondItem
)
{
    const char* preview = *selectedIndex == 0 ? firstItem : secondItem;

    if (ImGui::BeginCombo(label, preview))
    {
        if (ImGui::Selectable(firstItem, *selectedIndex == 0))
        {
            *selectedIndex = 0;
        }

        if (ImGui::Selectable(secondItem, *selectedIndex == 1))
        {
            *selectedIndex = 1;
        }

        ImGui::EndCombo();
    }
}

/*
 * Purpose: Renders and runs the complete Dear ImGui inventory interface.
 * Parameters: inventoryFilePath - CSV path used by load and save actions.
 * Return value: None.
 */
void renderUI(const char* inventoryFilePath)
{
    WNDCLASSEXW windowClass = {
        sizeof(WNDCLASSEXW),
        CS_CLASSDC,
        windowProcedure,
        0L,
        0L,
        GetModuleHandle(nullptr),
        nullptr,
        nullptr,
        nullptr,
        nullptr,
        L"InventoryManagerWindow",
        nullptr
    };

    RegisterClassExW(&windowClass);

    HWND window = CreateWindowW(
        windowClass.lpszClassName,
        L"Inventory Manager",
        WS_OVERLAPPEDWINDOW,
        100,
        100,
        1280,
        760,
        nullptr,
        nullptr,
        windowClass.hInstance,
        nullptr
    );

    if (!createDeviceD3D(window))
    {
        cleanupDeviceD3D();
        UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);
        return;
    }

    ShowWindow(window, SW_SHOWDEFAULT);
    UpdateWindow(window);

    IMGUI_CHECKVERSION();
    ImGui::CreateContext();
    ImGuiIO& io = ImGui::GetIO();
    io.ConfigFlags |= ImGuiConfigFlags_NavEnableKeyboard;

    loadInterfaceFont();
    int currentTheme = calmNightTheme;
    applyAppTheme(currentTheme);

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(d3dDevice, d3dDeviceContext);

    bool done = false;
    int currentLanguage = englishLanguage;
    int selectedIndex = -1;
    int sortFieldChoice = sortByPrice;
    int sortAlgorithmChoice = quickSortAlgorithm;
    int quantityFilter = -1;
    char nameFilter[maxNameLength] = "";
    char newName[maxNameLength] = "";
    float newPrice = 1.0f;
    int newQuantity = 1;
    int editQuantity = 0;
    char statusText[256] = "Ready.";

    while (!done)
    {
        MSG message;
        while (PeekMessage(&message, nullptr, 0U, 0U, PM_REMOVE))
        {
            TranslateMessage(&message);
            DispatchMessage(&message);

            if (message.message == WM_QUIT)
            {
                done = true;
            }
        }

        if (done)
        {
            break;
        }

        ImGui_ImplDX11_NewFrame();
        ImGui_ImplWin32_NewFrame();
        ImGui::NewFrame();

        const uiText& t = texts[currentLanguage];

        ImGui::SetNextWindowPos(ImVec2(0.0f, 0.0f), ImGuiCond_Always);
        ImGui::SetNextWindowSize(io.DisplaySize, ImGuiCond_Always);
        ImGui::Begin(
            "InventoryRoot",
            nullptr,
            ImGuiWindowFlags_NoDecoration
                | ImGuiWindowFlags_NoMove
                | ImGuiWindowFlags_NoResize
        );

        ImGui::TextColored(themePalettes[currentTheme].buttonHover, "%s", t.title);
        ImGui::SameLine();
        ImGui::TextDisabled("  %s: %d", t.products, getProductCountForDisplay());

        ImGui::BeginChild("navbar", ImVec2(0.0f, 58.0f), true);
        if (ImGui::Button(t.theme, ImVec2(128.0f, 0.0f)))
        {
            ImGui::OpenPopup("settingsPopup");
        }
        ImGui::SameLine();
        if (ImGui::Button(t.addProduct, ImVec2(150.0f, 0.0f)))
        {
            ImGui::OpenPopup("addPopup");
        }
        ImGui::SameLine();
        if (ImGui::Button(t.updateQuantity, ImVec2(170.0f, 0.0f)))
        {
            ImGui::OpenPopup("editPopup");
        }
        ImGui::SameLine();
        if (ImGui::Button(t.sortProducts, ImVec2(150.0f, 0.0f)))
        {
            ImGui::OpenPopup("sortPopup");
        }
        ImGui::SameLine();
        if (ImGui::Button(t.save, ImVec2(120.0f, 0.0f)))
        {
            ImGui::OpenPopup("filePopup");
        }
        ImGui::SameLine();
        ImGui::TextDisabled("%s: %s", t.status, statusText);
        ImGui::EndChild();

        if (ImGui::BeginPopup("settingsPopup"))
        {
            ImGui::TextUnformatted(t.theme);
            if (ImGui::BeginCombo("##themeCombo", themePalettes[currentTheme].name))
            {
                for (int i = 0; i < themeCount; ++i)
                {
                    if (ImGui::Selectable(themePalettes[i].name, currentTheme == i))
                    {
                        currentTheme = i;
                        applyAppTheme(currentTheme);
                    }
                }
                ImGui::EndCombo();
            }

            ImGui::Spacing();
            ImGui::TextUnformatted(t.languageLabel);
            if (ImGui::BeginCombo("##languageCombo", texts[currentLanguage].languageName))
            {
                for (int i = 0; i < languageCount; ++i)
                {
                    const bool selected = currentLanguage == i;

                    if (ImGui::Selectable(texts[i].languageName, selected))
                    {
                        currentLanguage = i;
                    }

                    if (selected)
                    {
                        ImGui::SetItemDefaultFocus();
                    }
                }

                ImGui::EndCombo();
            }
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("addPopup"))
        {
            ImGui::TextUnformatted(t.addProduct);
            ImGui::InputText(t.productName, newName, sizeof(newName));
            ImGui::InputFloat(t.price, &newPrice, 0.10f, 1.0f, "%.2f");
            ImGui::InputInt(t.quantity, &newQuantity);

            if (ImGui::Button(t.add, ImVec2(220.0f, 0.0f)))
            {
                if (addNewProduct(newName, newPrice, newQuantity))
                {
                    copyText(statusText, t.productAdded);
                    newName[0] = '\0';
                    newPrice = 1.0f;
                    newQuantity = 1;
                    ImGui::CloseCurrentPopup();
                }
                else
                {
                    copyText(statusText, t.invalidInput);
                }
            }
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("editPopup"))
        {
            if (selectedIndex >= 0)
            {
                product selectedItem = {};
                getProductForDisplay(selectedIndex, &selectedItem);
                ImGui::TextUnformatted(selectedItem.name);
                ImGui::Text("%s: %.2f", t.price, selectedItem.price);
                ImGui::InputInt(t.quantity, &editQuantity);

                if (ImGui::Button(t.updateQuantity, ImVec2(220.0f, 0.0f)))
                {
                    if (updateProductQuantity(selectedIndex, editQuantity))
                    {
                        copyText(statusText, t.quantityUpdated);
                    }
                    else
                    {
                        copyText(statusText, t.invalidInput);
                    }
                }

                if (ImGui::Button(t.deleteProduct, ImVec2(220.0f, 0.0f)))
                {
                    if (deleteProductByIndex(selectedIndex))
                    {
                        selectedIndex = -1;
                        copyText(statusText, t.productDeleted);
                        ImGui::CloseCurrentPopup();
                    }
                }
            }
            else
            {
                ImGui::TextWrapped("%s", t.selectRow);
            }
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("sortPopup"))
        {
            renderLocalizedCombo(
                t.sortField,
                &sortFieldChoice,
                t.sortByPrice,
                t.sortByQuantity
            );
            renderLocalizedCombo(
                t.sortAlgorithm,
                &sortAlgorithmChoice,
                t.quickSort,
                t.bogoSort
            );

            if (ImGui::Button(t.applySort, ImVec2(220.0f, 0.0f)))
            {
                const bool sorted = sortInventory(
                    static_cast<sortField>(sortFieldChoice),
                    static_cast<sortAlgorithm>(sortAlgorithmChoice)
                );

                copyText(statusText, sorted ? t.sorted : t.bogoBlocked);
                selectedIndex = -1;
                ImGui::CloseCurrentPopup();
            }
            ImGui::EndPopup();
        }

        if (ImGui::BeginPopup("filePopup"))
        {
            ImGui::Text("%s: %.2f", t.totalValue, calculateInventoryTotalValue());

            if (ImGui::Button(t.save, ImVec2(160.0f, 0.0f)))
            {
                copyText(
                    statusText,
                    saveInventoryToFile(inventoryFilePath) ? t.saved : t.invalidInput
                );
            }

            ImGui::SameLine();

            if (ImGui::Button(t.reload, ImVec2(160.0f, 0.0f)))
            {
                selectedIndex = -1;
                copyText(
                    statusText,
                    loadInventoryFromFile(inventoryFilePath) ? t.loaded : t.invalidInput
                );
            }
            ImGui::EndPopup();
        }

        ImGui::BeginChild("contentPanel", ImVec2(0.0f, 0.0f), true);
        ImGui::TextUnformatted(t.products);
        ImGui::SameLine();
        ImGui::TextDisabled("%s: %.2f", t.totalValue, calculateInventoryTotalValue());
        ImGui::Separator();

        ImGui::SetNextItemWidth(360.0f);
        ImGui::InputText(t.searchName, nameFilter, sizeof(nameFilter));
        ImGui::SameLine();
        ImGui::SetNextItemWidth(210.0f);
        ImGui::InputInt(t.exactQuantity, &quantityFilter);
        ImGui::SameLine();

        if (ImGui::Button(t.clearFilters))
        {
            nameFilter[0] = '\0';
            quantityFilter = -1;
        }

        if (selectedIndex >= 0)
        {
            product selectedItem = {};
            getProductForDisplay(selectedIndex, &selectedItem);
            ImGui::TextDisabled(
                "%s: %s  |  %.2f  |  %d",
                t.status,
                selectedItem.name,
                selectedItem.price,
                selectedItem.quantity
            );
        }
        else
        {
            ImGui::TextDisabled("%s", t.selectRow);
        }

        renderProductsTable(&selectedIndex, &editQuantity, nameFilter, quantityFilter, t);
        ImGui::EndChild();

        ImGui::End();

        ImGui::Render();

        const ImVec4 clear = themePalettes[currentTheme].window;
        const float clearColor[4] = { clear.x, clear.y, clear.z, clear.w };
        d3dDeviceContext->OMSetRenderTargets(1, &mainRenderTargetView, nullptr);
        d3dDeviceContext->ClearRenderTargetView(mainRenderTargetView, clearColor);
        ImGui_ImplDX11_RenderDrawData(ImGui::GetDrawData());
        swapChain->Present(1, 0);
    }

    ImGui_ImplDX11_Shutdown();
    ImGui_ImplWin32_Shutdown();
    ImGui::DestroyContext();

    cleanupDeviceD3D();
    DestroyWindow(window);
    UnregisterClassW(windowClass.lpszClassName, windowClass.hInstance);
}
