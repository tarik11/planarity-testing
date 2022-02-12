# planarity-testing
Planarity testing using region/faces algorithm complaxity O(n^4)



DOKUMENTATION

Prirodno-matematički fakultet Sarajevo

Zmaja od Bosne 33-35,

Profesor: Esmir Pilav,

Asistent: Admir Beširević,

71 000 Sarajevo, Bosna i Hercegovina,

Tel.: +387 (0)33 954 700, 294 700;

[pmf@pmf.unsa.ba](mailto:pmf@pmf.unsa.ba)

  
  
  
  
  
  
  
  

ANALIZA I SINTEZA ALGORITAMA

  

Planarno testiranje

  
  
  
  
  
  
  
  
  
  
  
  
  
  

[UVOD  2](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.gboqnw2bpibs)

[Općenito  2](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.uhne1lcoyfkq)

[Teoreme iz grafova  3](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.d06jd1jtc19)

[Funkcije korištene za implementaciju  4](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.rblvmqu17aiu)

[1. isCyclic  4](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.l67mj5knti92)

[2. DFSPut  5](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.n906x9nct8fv)

[3. PutIzmedjuDvaDodana  6](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.6r40f9lgd8l7)

[4. PutIzmedjuDvaKojaNisuDodana  7](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.rjql5gb8rqt)

[5. ModifikujPostojeciPut  8](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.49ghvsbn5q97)

[6. BrojZajednickihRegija  8](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.26h78wbjzy0t)

[7. ModifikujDodaneGrane  9](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.1xi8bhs3nrt0)

[8. DaLiCvorImaObjeRegije  9](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.bmukd18hoeg8)

[9. ModifikujRegije  10](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.l6qwztemxh5y)

[10. PostaviNizove  11](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.767x8g9rboe9)

[11. TestPlanarnosti  12](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.36rutiikctx)

[Analiza kompleksnosti  15](https://docs.google.com/document/d/1Bf_iWQll3GYC0bO9TtZyrDVLajd_NlxULGWBC8Qm2NI/edit#heading=h.ol3ilse7itm8)

  
  
  
  
  
  
  
  

# UVOD

## Općenito

U ovome odjelu ćemo objasniti pesudo kod za implementaciju planarnog testiranja korištenjem regije.

Za graf kažemo da je planaran ako se može nacrtati u ravni tako da se nikoje dvije grane ne sijeku. Za ulaz koristimo dva konektovan graf.

Za dati graf G, prvi korak algoritma jeste da pronađemo ciklus, ako ne postoji ciklus tada je G stablo i time završavamo algoritam.

Kada nađemo ciklus prvo što radimo jeste označimo regije sa 1 unutrašnjost ciklusa, 2 vanjski dio ciklusa

Sljedeći korak jest da nađemo put sa jednog čvora ciklusa u drugi čvor ciklusa.

Tada za put pitamo da li je blokiran tako što uporedimo regije čvorova na ciklusu. Ako ne postoji zajednička regija ćvorova tad je put blokiran i algoritam se završava.

Sa druge strane ako postoji regija koju djele tada dodajemo put u zajedničku regiju, te taj put djelu regiju na dvije regije.

U sljedećem koraku ćemo definisat forsirane kao dva čvora koji imaju samo jednu zajedničku regiju.

Ako postoji neki forsiran put njega odma probamo dodati.

Algoritam se nastavlja dok graf G ne bude jednak novom grafu GT

  
  
  
  
  
  
  

## Teoreme iz grafova

Definicija1: Za graf G(V, E) kažemo da je konektovan ako za svaka 2 čvor x. y iz G, postoji put od x do y. 2-konektovan graf je konektovan graf za koje vrijedi da za svaki čvor X iz G vrijedi G-X je konektovan graf.

Teorema1:

Za planaran graf G(V, E) imamo da je maksimalan broj grana E >= 3V - 6

Ovu teoremu ćemo koristiti kao uslov da graf nije planaran.

Teorema2:

Broj grana, u oznaci R, u planarnom grafu G(V, E) je R = E - V + 2

  
  
  
  
  
  
  
  
  
  
  
  
  
  
  
  

# Funkcije korištene za implementaciju

  

## 1. isCyclic

Ova funkcija prima vecktor po referenci i vrača true ili false da li postoji ciklus.

Ova funkciju sam uzeo sa stranice

[https://www.geeksforgeeks.org/detect-cycle-undirected-graph/](https://www.geeksforgeeks.org/detect-cycle-undirected-graph/)

Promjenio sam samo da prima vector i da dodjem u vector dati ciklus.

Ciklus pronalazimo tako što DFS-om prolazimo kroz čvorove i pokušavamo naći ciklus.

![](https://lh5.googleusercontent.com/HXF_Nfjccsht_7ijZg7nSO0Yh9dHXfjnrBP6s7lzII4YS9NIIibzYQZeoUc-KwXqOScmKSf0_oGlSarNBjJibefnPaxPrvrvq-5IEPK2x5dcqXGKxwUkiMUzHmYWq2v5OJCAQtPW)

  
  
  
  

## 2. DFSPut

Ovu funkciju koristiom da nađemo put od jednog početnog čvora na ciklusu do drugog.

Ova funkcija prima dodane_cvorove da provjerimo je li čvor dodan, dodane_grane da provjerimo je li grana već dodana, Funkcija vraća put od poćetnog do dodanog ili prazan vector.

![](https://lh6.googleusercontent.com/8m__8a4C1Jl0T9tUF5jkfTBmjT6732BvXSXKx_M6UaOogYXebopPp1UsSnX3kcpdumDQ1u9nRCI6fnvXHWMUp9qJsB5JPgTh5sfx8eAG2hNY06gN_ks_6VXI6W8PnCWlUNXULnXh)

Funkcija je jednostavno DFS - om prolazimo kroz čvorove i dodajemo na put one koje nisu oznacene u vectori dodatnih čvorova

  
  
  
  
  
  

## 3. PutIzmedjuDvaDodana

U ovoj funcije BFS prelaskom pronalazimo put izmedju dva dodana čvora.

Funkciju koristimo kako bi znali koji se put pokriva novo dodanom regijom.

Funkcija prima niz dodanih cvorova i matricu regija. Prolaskom kroz početnog do krajnjeg čvora obradjujemo samo one čvorove i grane koje su dodane na ciklus.

![](https://lh4.googleusercontent.com/apD1br7PkdU43gyAcLA7l2-a5uovZPm7UG2rYYjElyIXCDi8T_HBHks_zGhCVClqwVfKoqOEHeq02LgLXK2wMQDEfh1j9E72uH3OkTN-Ci3ri_M93JYafVaB-HIevDiF-mkS-RBW)

  
  
  

## 4. PutIzmedjuDvaKojaNisuDodana

Analogno, prethodnoj funkciji ovou funkciju korstimo da nadjemo put izmedju dva zadana čvora koja nisu u dodanim čvorovima.

Koristimo da nađemo put između dva forsirana čvora.

![](https://lh6.googleusercontent.com/HTpn_WvhytfHQL0rpAy2h6tz9oCmvS8e0ZTHfZUcnjs_nSobwkgYKgfjkUySRZFTYUvUpvppKFkCiZYuU_bft62rE-eSctcyi_Rz7fslFq3HuhWgGgdFB9YGI0LgJB_mKxCVrojw)

  
  
  
  
  

## 5. ModifikujPostojeciPut

U ovoj funkciji šaljemo matricu regija i put koji smo pronašli i na čvoreve ovog puta ažuriramo novu regiju i zajednićku regiju.

![](https://lh5.googleusercontent.com/kEBZMnOWGfMvQOOg8cElteMRH68UhyWU37pHRTIWtHuhXFCJiSXZICHbafqDwl7HltRZzifuv27Ha1Zctpqeec40GVPuI9bcHFEI7cqUp6DtThZOkTVOQ-TzM1AyC_zkNuusk9Hd)

  

## 6. BrojZajednickihRegija

Ova funkcija vraća broj zajednićkih regija između dva čvora.

![](https://lh4.googleusercontent.com/NK6UWJtQkNJeUvl_kzmy0nxegrBycUWgvLSNWyj6h8BSWv_f3zyazR-v2-IP0lR11zwX68e_5kygHmM7zwcORz9_ZlGf8iKF44ZUwa_uPD1VuDhzjaePDPUNgETeUTY2bAHWrYSH)

  
  
  
  
  
  

## 7. ModifikujDodaneGrane

0vu funkciju koristimo kako bi dodali grane u dodane_grane sa put kojeg smo prethodno pronašli.

  

![](https://lh3.googleusercontent.com/9hc8lCwqNV6UF5pZ2PyOmieAA6qQkp5XwDhcVNcoKyE-ZCf7d51wuwodpYBaayuJIcLPWAy0wuWuPH4_rLvEe_cHr8ihEXMhr6dgeqbukuptWca_XrEvZWoX2_yqIuPbiZBdl-c7)

  

## 8. DaLiCvorImaObjeRegije

Ovu funkciju koristimo kako bi provjerili da li cvor ima obje regije koje su poslane.

![](https://lh6.googleusercontent.com/5s3aeDyFHZMUn7nmjAqw8S6AM7wz4qB9as_8xCberS2PpQFlpKTff4pQJfZsuGBQwDLQ2rkbUDTultOYhzSOnvlrzQvI4DO-mfF05CeVKH7scvX6OKzuOcetOCEvxtsjEbr96EwV)

  
  
  
  
  

## 9. ModifikujRegije

Funkciju koristimo da čvorove puta oznacimo zajedničku regiju kroz koju prolaze i novu regiju. Te dodamo put u dodatne čvorove.

![](https://lh4.googleusercontent.com/m_XhN5kGmyyaPYmCO7pnAt-HRD92Z0FhDwsiQHTDOLDFU53WI4LiKUwxfMU8k6GM3vLC9c9HXpNpPpwrbv1qpxgjdHuUQndL7JahyAha_fU_HCCwm3SGrdisNwnNvdzyWbrC4F7h)

  
  
  
  
  
  
  
  
  
  
  
  
  
  

## 10. PostaviNizove

Ovu funkciju koristimo kako bi ažurirali dodane_grane, dodane_cvorove, regije_cvorova,

za pronalaženi ciklus

![](https://lh5.googleusercontent.com/YjtoN-6LI6ZMXuh6Gmlb84q3lqvCO1A19Q56yZQP2oxqm9XyXP95qrPoGtuNxBHfgIAKWYKxNs8ueZc8GhjFLZMXNBd7qvsJhb1JVm13HPQA8vtiGfDlLWwHuhCE-kQR03T9_TAL)

  
  
  
  
  
  

## 11. TestPlanarnosti

Algoritam počinjemo tako što ispitujemo slučaj iz Teoreme 2

![](https://lh5.googleusercontent.com/I6JtH7P_2Nvgk2wzqFn21J_mBCgmKRu5Rn5TekBCSSL1OMWFevunCkxZdMXGoJtU5bQJZY-0QGqiJlS7_JPiwDAC07yIUXdUDVG2EHDUPblQzGZ-qXCsMwADQpTpziZrWaPScy7x)

Onda pokušamo naći ciklus ako ne postoji onda je stablo i vraćamo da je planaran graf

![](https://lh4.googleusercontent.com/vYWQSKFIZxpeBXOqL4HHQ9c5Q4RD8NYmRhXU1yPcpMw6hKqge7ZFpMhXpJCzzuLrR5Msr29STW9I_qFETQAAQlY_vm1OuLTioXR1ALM34-7IM0UwHTg_qQu6zaLKbsFWWRnrSpBR)

Sljedeči korak ulazimo u while petlju uslov zaustavljanja je kada prođemo kroz sve čvorove ili pređemo broj regija.

![](https://lh4.googleusercontent.com/fJl0-v2XweCV9rgcaoY5w8y0n20sFMjL2C4X2egUjw3eWZCRNScmjiESTk2fiyzBbtnDOpFdWqKxNpwC0wpKl0Ynj1uuzYaRHgwWx59t9l5UM36EwwsojG1Ts5pO6_28A9qDJ9px)

  
  
  
  

Dakle, while petljom prolazimo kroz cvoreve i sve njegove grane.

![](https://lh6.googleusercontent.com/EWeEroEF2QF128zp3LPO0UG0U8JhKzIHEi-inr2LdH-oIFNOTs9OxIMZ9Fgb-ABoRo6U4DfcmJFVa-ESU8xmCxVJbszQYlP40KAJrD1Hl3IdLjDAQjKtj26U7anl7J4yN4vwWzcs)

Nalazimo put ako postoji od trenutnog čvora do ciklusa, onda povečevamo regiju,

pronalazimo zajedničku regiju ako ne postoji vrćamo da graf nije planaran.

Ako postoje regije modifikujemo regije.

![](https://lh5.googleusercontent.com/tLVFDW82MUxk-DxDTniui4Cr8oMWVXvi1MNO6jhDuyJ2XfIdHCdLNuO5N81LcHgIHF3xna25fVKn20YXbKnW6FyCnX-uddGyKAwDhPd7aW09QzIOrONAppELbuTFLoNOBVEdJQjy)

Nakon toga pokušavamo naći put2 put koji novo dodani put može pokriti odnosno promjeniti mu regiju. Onda modifukujemo mu regiju, pa modifikujemo grane dodanog puta.

![](https://lh3.googleusercontent.com/8a0DsgDhSGgDLhT_Z1zOLcocF8qlccYadip64eLREw-5wQ1JbM-Rv5LhHHScym5o8-QDdqRSY5Za_6sETDM3_xvtWlzytAfMDJorG5fG-8S34YLzYl8Ud-VjHlziMnf4Xt6lgZ00)

  
  

Poslije toga pogledamo da li postoje dva forsirana čvora ako postoje dodajemo ih na vector i kasnije ispitamo za njih da li postoji put izmedju njih.

![](https://lh3.googleusercontent.com/tcK2swKFeXMwgVbxJdqE8JkApFdn90Dsutj2Zla0l3Iazmg_RNjBr_dLIS4jNoOcUM5aGcOLrLubZ_6n2vuezOGAcRM6ShL6ejgXJ_XA8Ok2MJJikS4jfON5Uf8dITh7XjThrUP4)

Isto tako gledamo blokirane odnosno da li nema zajedničke regije između svaka dva ćvora.

![](https://lh6.googleusercontent.com/vn8i7vqsammoogP8ftL0C0ATUQdPcqUcg6B8H9-8guwADchIeD08Y3pRMa0CUSrmOnPZ8shmgrV4fIj-_nmeAHqgDbrTgydyll8q8TbQdAFTaWVQJG9BUNzlwAbvBOqyqeNnQ3Mo)

  
  
  
  
  
  
  

Kada vector blokiranih nije prazan data za dva čvora testiramo da li ima put između njih,

ako postoji tada dati graf nije planaran. Ako ne postoji tada nastavljamo da testiramo ostale parove, no ako putu možemo promjeniti regiju tako da taj prethodni par čvorova ne bude blokiran to činimo i to činimo samo na jednom takvom čvoru.

![](https://lh5.googleusercontent.com/cmtoaqnmIA4IeQA23dk3reeS-bUeS6Wg2QwbU30vD-oh9FgP4uPVexD1SxOn0WwfC6cy8ENdnjYrvNvpMYNOq-ptnScP1GQj6Sn7tA-gnT_pGw5B_AZQ7XuFcm0PA39Z8oa21KB8)

  
  
  
  
  

# Analiza kompleksnosti

Poznato nam je E i R, broj grana i broj regija, ovisi od V. Imamo da je R = E-V+2, a gornja granica od E < 3V - 6 dakle možemo i procijeniti kao V.

Imamo da funkcije koje koristimo za pronalazak put i ciklusa su kompleksnost O(min(V+E)) odnosno O(V) zbog toga što koristimo BFS ili dfs za njihov pronalazak.

Te svaka funkcija koju koristimo za modifikaciju puta i pronalaženja zajedničke regije nas košta O(R), odnosno O(V).

No, pošto dodavanje forsiranih i blokiranih koristimo dvije for petlje ciklus i put ćija dužina može biti V, to znači da je kompleksnost O(V²­), što znači da vanjska petlja mora proći kroz te parove to je i kompleksnost vanjske petlje O(V²).

Tada je kompleksnost cijelog algoritma O(n^4).

Prostorna kompleksnost ovog algoritma je O(V²) jer alociramo matricu kako bi čuvali regije i grane.
