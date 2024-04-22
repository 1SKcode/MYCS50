--названия всех школьных округов и количества учеников, обучающихся в каждом
SELECT "name", "pupils" FROM "districts" JOIN "expenditures" ON "expenditures"."district_id" = "districts"."id";
