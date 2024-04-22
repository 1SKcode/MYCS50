--названия школ (государственных или чартерных) которые сообщили о 100%-ном уровне выпуска
SELECT "name"
FROM "schools"
WHERE "id" IN (
    SELECT "school_id"
    FROM "graduation_rates"
    WHERE "graduated" = 100
);
