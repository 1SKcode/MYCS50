-- название (или названия) школьного округа (округов) с наименьшим количеством учеников.
SELECT DISTINCT "name"
FROM "districts"
WHERE "id" = (
    SELECT "district_id"
    FROM "expenditures"
    GROUP BY "pupils"
    ORDER BY "pupils" ASC
);
