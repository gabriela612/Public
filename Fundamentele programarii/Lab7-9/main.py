from Repository import RepoSf
from Repository import RepoDf
from Repository import RepoNf
from Service import ServS
from Service import ServD
from Service import ServN
from UI import Consola
from Domain import ValidatorS
from Domain import ValidatorD
from Domain import ValidatorN
from Repository import Teste_repo


Teste_repo()
repoS = RepoSf()
repoS.Citire_fisier()
repoD = RepoDf()
repoD.Citire_fisier()
repoN = RepoNf()
repoN.Citire_fisier()
valiS = ValidatorS()
valiD = ValidatorD()
valiN = ValidatorN()
srvS = ServS(repoS, valiS)
srvD = ServD(repoD, valiD)
srvN = ServN(repoN, valiN, repoS, repoD)

ui = Consola(srvS, srvD, srvN)
ui.Inceput_ui()
