
```cpp

for(const nlohmann::json& antenna : atributes["antennas"])

{

this->vectorTx.emplace_back({

(antenna)["lat"].get<double>(),

(antenna)["lon"].get<double>(),

(*it)["height"].get<float>(),

(*it)["type"].get<std::string>(),

(*it)["id"].get<std::string>(),

(*it)["frequency"].get<float>()

});

}


antenna::antenna(double lat, double lon, float height, std::string type, std::stringid, float frequency) : type(type), lat(lat), lon(lon)
{

this->parameters.lat = lat;

this->parameters.lon = lon;

this->parameters.alt = height;

this->type = type;

this->id = id;

this->frequency = frequency;

}


double calcularPerdida (const double lat, const double lng, const float height, const float terrain)

{

}

double calcularPerdida2 (const double lat, const double lng, const float height)

{

}

std::vector<double> distance::get_arealoss(double top_lat , double top_lng, double bot_lat, double bot_lng, struct site tx, float frequency
                        , std::function<double(const double lat, const double lng, const int pos)> obtenerPerdida)
{

for(int i =
0; i < amount_lng; i++){

for(int j =
0; j < amount_lat; j++){


obtenerPerdida (i, j, i + j * amount_lat);

}

}

}

***

***

***


{

std::vecctor<double> height = servidor.pedir();

std::vector<double> tipo_terreno;

std::function<double (const double lat, const double lng, const int pos) accion;

switch (algoritmo)

{

case HATA:

accion = [height,tipo_terreno](const double lat, const double lng, const int pos)
{
    calcularPerdida(lat, lng,height[pos], tipo_terreno[pos])
};

case EIBERT_KULMAN:

accion = [height](constdouble lat, const double lng, const int pos){

calcularPerdida2(lat, lng, height[pos],)

};

}

get_arealoss(..., );

}

std::vector<double> pathloss;

pathloss.reserve(sizeof(double)*puntosQueTengo)

-----------------------------------

std::function<double (const double lat, const double lng, const int pos) accion;

switch (algoritmo)

{

case 
HATA:

accion = [height,
tipo_terreno](const
double 
lat, const 
double lng, 
const int 
pos){

calcularPerdida(lat, lng)

};

case 
EIBERT_KULMAN:

std::vecctor<double> height =
servidor.pedir(height);

std::vecctor<double> tipo_terreno =
servidor.pedir(tipo_terreno);

accion = [&height, &tipo_terreno](const double lat, const double lng, const int pos){

calcularPerdida2(lat, lng, height[pos], tipo_terreno[pos])

};

}


for(const nlohmann::json& posicion : atributes["antennas"])

{

accion(posicion.lat,
posicion.lng,
posicion.indice);

}


class Posiciones {

class Iterador {

lat

lng

indice

bool fin

};

Posiciones::Iterador
begin() {

}

Posiciones::Iterador
end() {


}


bool 
operator!= () {

return fin;

}

bool 
operator++ () {

lat

}

bool 
operator-- () {

lat

}

};


```

