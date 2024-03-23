import Repo
import Domain
import Service
import UI

Repo.teste()
Domain.teste()
Service.teste()

repo = Repo.Repo("melodii.txt")
repo.Citire_fisier()
vali = Domain.Validator()
serv = Service.Serv(repo, vali)
c = UI.Consola(serv)
c.Inceput()