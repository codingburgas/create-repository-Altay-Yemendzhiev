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

static void applyAppTheme(bool darkTheme)
{
    ImGuiStyle& style = ImGui::GetStyle();
    style.WindowRounding = 6.0f;
    style.FrameRounding = 5.0f;
    style.PopupRounding = 5.0f;
    style.ScrollbarRounding = 5.0f;
    style.GrabRounding = 5.0f;
    style.WindowBorderSize = 0.0f;
    style.FrameBorderSize = 0.0f;
    style.ItemSpacing = ImVec2(10.0f, 8.0f);
    style.WindowPadding = ImVec2(16.0f, 14.0f);
    style.FramePadding = ImVec2(10.0f, 7.0f);

    ImVec4* colors = style.Colors;
    const ImVec4 imperialBlue = colorFromHex(0x0a, 0x24, 0x63);
    const ImVec4 blueBell = colorFromHex(0x3e, 0x92, 0xcc);
    const ImVec4 snow = colorFromHex(0xff, 0xfa, 0xff);
    const ImVec4 magentaBloom = colorFromHex(0xd8, 0x31, 0x5b);
    const ImVec4 carbonBlack = colorFromHex(0x1e, 0x1b, 0x18);

    colors[ImGuiCol_Text] = darkTheme ? snow : carbonBlack;
    colors[ImGuiCol_TextDisabled] = darkTheme
        ? colorFromHex(0xa7, 0xb8, 0xd3)
        : colorFromHex(0x67, 0x6d, 0x76);
    colors[ImGuiCol_WindowBg] = darkTheme ? carbonBlack : snow;
    colors[ImGuiCol_ChildBg] = darkTheme
        ? colorFromHex(0x25, 0x28, 0x32)
        : colorFromHex(0xf0, 0xf6, 0xfb);
    colors[ImGuiCol_PopupBg] = colors[ImGuiCol_ChildBg];
    colors[ImGuiCol_Border] = darkTheme
        ? colorFromHex(0x3e, 0x92, 0xcc, 0.45f)
        : colorFromHex(0x0a, 0x24, 0x63, 0.25f);
    colors[ImGuiCol_FrameBg] = darkTheme
        ? colorFromHex(0x2d, 0x34, 0x47)
        : colorFromHex(0xff, 0xff, 0xff);
    colors[ImGuiCol_FrameBgHovered] = colorFromHex(0x3e, 0x92, 0xcc, 0.42f);
    colors[ImGuiCol_FrameBgActive] = blueBell;
    colors[ImGuiCol_TitleBg] = imperialBlue;
    colors[ImGuiCol_TitleBgActive] = imperialBlue;
    colors[ImGuiCol_MenuBarBg] = imperialBlue;
    colors[ImGuiCol_Button] = blueBell;
    colors[ImGuiCol_ButtonHovered] = colorFromHex(0x5a, 0xaa, 0xde);
    colors[ImGuiCol_ButtonActive] = magentaBloom;
    colors[ImGuiCol_Header] = colorFromHex(0x3e, 0x92, 0xcc, 0.55f);
    colors[ImGuiCol_HeaderHovered] = blueBell;
    colors[ImGuiCol_HeaderActive] = magentaBloom;
    colors[ImGuiCol_CheckMark] = magentaBloom;
    colors[ImGuiCol_SliderGrab] = blueBell;
    colors[ImGuiCol_SliderGrabActive] = magentaBloom;
    colors[ImGuiCol_Tab] = darkTheme ? colorFromHex(0x23, 0x39, 0x63) : colorFromHex(0xd9, 0xeb, 0xf8);
    colors[ImGuiCol_TabHovered] = blueBell;
    colors[ImGuiCol_TabActive] = imperialBlue;
    colors[ImGuiCol_TableHeaderBg] = imperialBlue;
    colors[ImGuiCol_TableRowBg] = darkTheme ? colorFromHex(0x22, 0x21, 0x20) : snow;
    colors[ImGuiCol_TableRowBgAlt] = darkTheme
        ? colorFromHex(0x28, 0x2e, 0x3b)
        : colorFromHex(0xee, 0xf6, 0xfc);
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
            | ImGuiTableFlags_Borders
            | ImGuiTableFlags_Resizable
            | ImGuiTableFlags_ScrollY,
        ImVec2(0.0f, 430.0f)
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
    applyAppTheme(true);

    ImGui_ImplWin32_Init(window);
    ImGui_ImplDX11_Init(d3dDevice, d3dDeviceContext);

    bool done = false;
    bool darkTheme = true;
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

        ImGui::TextColored(colorFromHex(0x3e, 0x92, 0xcc), "%s", t.title);
        ImGui::SameLine();
        ImGui::Text("  %s: %d", t.products, getProductCountForDisplay());
        ImGui::Separator();

        ImGui::BeginChild("leftPanel", ImVec2(340.0f, 0.0f), true);
        ImGui::TextUnformatted(t.controls);

        ImGui::Spacing();
        ImGui::TextUnformatted(t.theme);
        if (ImGui::RadioButton(t.dark, darkTheme))
        {
            darkTheme = true;
            applyAppTheme(true);
        }
        ImGui::SameLine();
        if (ImGui::RadioButton(t.light, !darkTheme))
        {
            darkTheme = false;
            applyAppTheme(false);
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

        ImGui::SeparatorText(t.addProduct);
        ImGui::InputText(t.productName, newName, sizeof(newName));
        ImGui::InputFloat(t.price, &newPrice, 0.10f, 1.0f, "%.2f");
        ImGui::InputInt(t.quantity, &newQuantity);

        if (ImGui::Button(t.add, ImVec2(-1.0f, 0.0f)))
        {
            if (addNewProduct(newName, newPrice, newQuantity))
            {
                copyText(statusText, t.productAdded);
                newName[0] = '\0';
                newPrice = 1.0f;
                newQuantity = 1;
            }
            else
            {
                copyText(statusText, t.invalidInput);
            }
        }

        ImGui::SeparatorText(t.updateQuantity);
        ImGui::InputInt(t.quantity, &editQuantity);

        if (ImGui::Button(t.updateQuantity, ImVec2(-1.0f, 0.0f)))
        {
            if (selectedIndex >= 0 && updateProductQuantity(selectedIndex, editQuantity))
            {
                copyText(statusText, t.quantityUpdated);
            }
            else
            {
                copyText(statusText, t.selectRow);
            }
        }

        if (ImGui::Button(t.deleteProduct, ImVec2(-1.0f, 0.0f)))
        {
            if (selectedIndex >= 0 && deleteProductByIndex(selectedIndex))
            {
                selectedIndex = -1;
                copyText(statusText, t.productDeleted);
            }
            else
            {
                copyText(statusText, t.selectRow);
            }
        }

        ImGui::SeparatorText(t.sortProducts);
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

        if (ImGui::Button(t.applySort, ImVec2(-1.0f, 0.0f)))
        {
            const bool sorted = sortInventory(
                static_cast<sortField>(sortFieldChoice),
                static_cast<sortAlgorithm>(sortAlgorithmChoice)
            );

            copyText(statusText, sorted ? t.sorted : t.bogoBlocked);
        }

        ImGui::SeparatorText(t.status);
        ImGui::TextWrapped("%s", statusText);
        ImGui::Text("%s: %.2f", t.totalValue, calculateInventoryTotalValue());

        if (ImGui::Button(t.save, ImVec2(154.0f, 0.0f)))
        {
            copyText(
                statusText,
                saveInventoryToFile(inventoryFilePath) ? t.saved : t.invalidInput
            );
        }

        ImGui::SameLine();

        if (ImGui::Button(t.reload, ImVec2(154.0f, 0.0f)))
        {
            selectedIndex = -1;
            copyText(
                statusText,
                loadInventoryFromFile(inventoryFilePath) ? t.loaded : t.invalidInput
            );
        }

        ImGui::EndChild();

        ImGui::SameLine();
        ImGui::BeginChild("tablePanel", ImVec2(0.0f, 0.0f), true);
        ImGui::TextUnformatted(t.products);
        ImGui::InputText(t.searchName, nameFilter, sizeof(nameFilter));
        ImGui::InputInt(t.exactQuantity, &quantityFilter);
        ImGui::SameLine();

        if (ImGui::Button(t.clearFilters))
        {
            nameFilter[0] = '\0';
            quantityFilter = -1;
        }

        renderProductsTable(&selectedIndex, &editQuantity, nameFilter, quantityFilter, t);
        ImGui::EndChild();

        ImGui::End();

        ImGui::Render();

        const float clearColor[4] = { 0.039f, 0.141f, 0.388f, 1.0f };
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
